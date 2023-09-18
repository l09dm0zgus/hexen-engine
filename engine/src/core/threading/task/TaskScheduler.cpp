#include "TaskScheduler.hpp"

#include "../counter/AtomicCounter.hpp"
#include "../counter/TaskCounter.hpp"
#include "../threads/Thread.hpp"
#include "Callbacks.hpp"
#include <array>

#if defined(HEXEN_WIN32_THREADS)
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
	#include <windows.h>
#elif defined(HEXEN_POSIX_THREADS)
	#include <pthread.h>
#endif

namespace hexen::engine::core::threading
{
	constexpr static unsigned failedPopAttemptsHeuristic = 5;
	constexpr static int initErrorDoubleCall = -30;
	constexpr static int initErrorFailedToCreateWorkerThread = -60;

	struct ThreadStartArgs
	{
		TaskScheduler *scheduler;
		unsigned threadIndex;
	};

	HEXEN_THREAD_FUNC_RETURN_TYPE TaskScheduler::threadStartFunction(vptr const arg)
	{
		auto *const threadArgs = reinterpret_cast<ThreadStartArgs *>(arg);
		auto *taskScheduler = threadArgs->scheduler;
		auto const index = threadArgs->threadIndex;

		// Clean up
		delete threadArgs;

		// Spin wait until everything is initialized
		while (!taskScheduler->isInitialized.load(std::memory_order_acquire))
		{
			// Spin
			HEXEN_PAUSE();
		}

		// Execute user threads start callback, if set
		const auto &callbacks = taskScheduler->callbacks;
		if (callbacks.onWorkerThreadStarted != nullptr)
		{
			callbacks.onWorkerThreadStarted(callbacks.context, index);
		}

		// Get a free fiber to switch to
		auto const freeFiberIndex = taskScheduler->getNextFreeFiberIndex();

		// Initialize tls
		taskScheduler->threadLocalStorage[index].currentFiberIndex = freeFiberIndex;
		// Switch
		taskScheduler->threadLocalStorage[index].threadFiber.switchToFiber(&taskScheduler->fibers[freeFiberIndex]);

		// And we've returned

		// Execute user threads end callback, if set
		if (callbacks.onWorkerThreadEnded != nullptr)
		{
			callbacks.onWorkerThreadEnded(callbacks.context, index);
		}

		// Cleanup and shutdown
		thread::endCurrentThread();
		HEXEN_THREAD_FUNC_END;
	}

	// This Task is never used directly
	// However, a function pointer to it is the signal that the task is a Ready fiber, not a "real" task
	// See @fiberStartFunction() for more details
	static void ReadyFiberDummyTask(TaskScheduler *taskScheduler, vptr arg)
	{
		(void) taskScheduler;
		(void) arg;
	}

	void TaskScheduler::fiberStartFunction(vptr arg)
	{
		auto *taskScheduler = reinterpret_cast<TaskScheduler *>(arg);

		if (taskScheduler->callbacks.onFiberAttached != nullptr)
		{
			taskScheduler->callbacks.onFiberAttached(taskScheduler->callbacks.context, taskScheduler->getCurrentFiberIndex());
		}

		// If we just started from the pool, we may need to clean up from another fiber
		taskScheduler->cleanUpOldFiber();

		std::vector<TaskBundle> taskBuffer;

		// Process tasks infinitely, until quit
		while (!taskScheduler->isQuit.load(std::memory_order_acquire))
		{
			auto waitingFiberIndex = invalidIndex;
			auto *tls = &taskScheduler->threadLocalStorage[taskScheduler->getCurrentThreadIndex()];

			bool readyWaitingFibers = false;

			// Check if there is a ready-pinned waiting fiber
			{
				std::lock_guard<std::mutex> guard(tls->pinnedReadyFibersLock);

				for (auto bundle = tls->pinnedReadyFibers.begin(); bundle != tls->pinnedReadyFibers.end(); ++bundle)
				{
					readyWaitingFibers = true;

					if (!(*bundle)->fiberIsSwitched.load(std::memory_order_acquire))
					{
						// The wait condition is ready, but the "source" threads hasn't switched away from the fiber yet
						// Skip this fiber until the next round
						continue;
					}

					waitingFiberIndex = (*bundle)->fiberIndex;
					tls->pinnedReadyFibers.erase(bundle);
					break;
				}
			}

			TaskBundle nextTask {};
			bool foundTask = false;

			// If nothing was found, check if there is a high priority task to run
			if (waitingFiberIndex == invalidIndex)
			{
				foundTask = taskScheduler->getNextHighPriorityTask(&nextTask, &taskBuffer);

				// Check if the found task is a ReadyFiber dummy task
				if (foundTask && nextTask.taskToExecute == ReadyFiberDummyTask)
				{
					// Get the waiting fiber index
					auto *readyFiberBundle = reinterpret_cast<ReadyFiberBundle *>(nextTask.taskToExecute.ArgumentsData);
					waitingFiberIndex = readyFiberBundle->fiberIndex;
				}
			}

			if (waitingFiberIndex != invalidIndex)
			{
				// Found a waiting task that is ready to continue

				tls->oldFiberIndex = tls->currentFiberIndex;
				tls->currentFiberIndex = waitingFiberIndex;
				tls->oldFiberDestination = FiberDestination::ToPool;

				const auto &callbacks = taskScheduler->callbacks;
				if (callbacks.onFiberDetached != nullptr)
				{
					callbacks.onFiberDetached(callbacks.context, tls->oldFiberIndex, false);
				}

				// Switch
				taskScheduler->fibers[tls->oldFiberIndex].switchToFiber(&taskScheduler->fibers[tls->currentFiberIndex]);

				if (callbacks.onFiberAttached != nullptr)
				{
					callbacks.onFiberAttached(callbacks.context, taskScheduler->getCurrentFiberIndex());
				}

				// And we're back
				taskScheduler->cleanUpOldFiber();

				// Get a fresh instance of TLS, since we could be on a new threads now
				tls = &taskScheduler->threadLocalStorage[taskScheduler->getCurrentThreadIndex()];

				if (taskScheduler->emptyQueueBehavior.load(std::memory_order::memory_order_relaxed) == EmptyQueueBehavior::Sleep)
				{
					tls->failedQueuePopAttempts = 0;
				}
			}
			else
			{
				// If we didn't find a high priority task, look for a low priority task
				if (!foundTask)
				{
					foundTask = taskScheduler->getNextNormalPriorityTask(&nextTask);
				}

				auto const behavior = taskScheduler->emptyQueueBehavior.load(std::memory_order::memory_order_relaxed);

				if (foundTask)
				{
					if (behavior == EmptyQueueBehavior::Sleep)
					{
						tls->failedQueuePopAttempts = 0;
					}

					nextTask.taskToExecute.execute();
					if (nextTask.counter != nullptr)
					{
						nextTask.counter->decrement();
					}
				}
				else
				{
					// We failed to find a Task from any of the queues
					// What we do now depends on emptyQueueBehavior, which we loaded above
					switch (behavior)
					{
						case EmptyQueueBehavior::Yield:
							thread::yieldThread();
							break;

						case EmptyQueueBehavior::Sleep:
						{
							// If we have a ready waiting fiber, prevent sleep
							if (!readyWaitingFibers)
							{
								++tls->failedQueuePopAttempts;
								// Go to sleep if we've failed to find a task failedPopAttemptsHeuristic times
								if (tls->failedQueuePopAttempts >= failedPopAttemptsHeuristic)
								{
									std::unique_lock<std::mutex> lock(taskScheduler->threadSleepLock);
									// Acquire the pinned ready fibers lock here and check if there are any pinned fibers ready
									// Acquiring the lock here prevents a race between readying a pinned fiber (on another threads) and going to sleep
									// Either this threads wins, then notify_*() will wake it
									// Or the other threads wins, then this threads will observe the pinned fiber, and will not go to sleep
									std::unique_lock<std::mutex> readyfiberslock(tls->pinnedReadyFibersLock);
									if (tls->pinnedReadyFibers.empty())
									{
										// Unlock before going to sleep (the other lock is released by the CV wait)
										readyfiberslock.unlock();
										taskScheduler->threadSleepCv.wait(lock);
									}
									tls->failedQueuePopAttempts = 0;
								}
							}

							break;
						}
						case EmptyQueueBehavior::Spin:
						default:
							// Just fall through and continue the next loop
							break;
					}
				}
			}
		}

		// Switch to the quit fibers

		if (taskScheduler->callbacks.onFiberDetached != nullptr)
		{
			taskScheduler->callbacks.onFiberDetached(taskScheduler->callbacks.context, taskScheduler->getCurrentFiberIndex(), false);
		}

		auto index = taskScheduler->getCurrentThreadIndex();
		taskScheduler->fibers[taskScheduler->threadLocalStorage[index].currentFiberIndex].switchToFiber(&taskScheduler->quitFibers[index]);

		// We should never get here
		printf("Error: FiberStart should never return");
	}

	void TaskScheduler::threadEndFunction(vptr arg)
	{
		auto *taskScheduler = reinterpret_cast<TaskScheduler *>(arg);

		// Wait for all other threads to quit
		taskScheduler->quitCount.fetch_add(1, std::memory_order_seq_cst);
		while (taskScheduler->quitCount.load(std::memory_order_seq_cst) != taskScheduler->numberOfThreads)
		{
			thread::sleepThread(50);
		}

		// Jump to the threads fibers
		auto threadIndex = taskScheduler->getCurrentThreadIndex();

		if (threadIndex == 0)
		{
			// Special case for the main threads fiber
			taskScheduler->quitFibers[threadIndex].switchToFiber(&taskScheduler->fibers[0]);
		}
		else
		{
			taskScheduler->quitFibers[threadIndex].switchToFiber(&taskScheduler->threadLocalStorage[threadIndex].threadFiber);
		}

		// We should never get here
		printf("Error: threadEndFunction should never return");
	}


	int TaskScheduler::initialize(TaskSchedulerInitOptions options)
	{
		settings = memory::make_unique<TaskSchedulerSettings>();

		options.fiberPoolSize = settings->getFiberPoolSize();
		options.threadPoolSize = settings->getUsedCores();


		// Sanity check to make sure the user doesn't double init
		if (isInitialized.load())
		{
			return initErrorDoubleCall;
		}

		callbacks = options.callbacks;

		// Initialize the flags
		emptyQueueBehavior.store(options.behavior);

		if (options.threadPoolSize == 0)
		{
			// 1 threads for each logical processor
			numberOfThreads = thread::getNumberOfHardwareThreads();
		}
		else
		{
			numberOfThreads = options.threadPoolSize;
		}

		// Create and populate the fiber pool
		fiberPoolSize = options.fiberPoolSize;
		fibers = new Fiber[options.fiberPoolSize];
		freeFibers = new std::atomic<bool>[options.fiberPoolSize];
		readyFiberBundles = new ReadyFiberBundle[options.fiberPoolSize];

		// Leave the first slot for the bound main threads
		for (u32 i = 1; i < options.fiberPoolSize; ++i)
		{
			fibers[i] = Fiber(524288, fiberStartFunction, this);
			freeFibers[i].store(true, std::memory_order_release);
		}
		freeFibers[0].store(false, std::memory_order_release);

		// Initialize threads and TLS
		threads = new thread::ThreadType[numberOfThreads];
#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable : 4316)// I know this won't be allocated to the right alignment, this is okay as we're using alignment for padding.
#endif							   // _MSC_VER
		threadLocalStorage = new ThreadLocalStorage[numberOfThreads];
#ifdef _MSC_VER
	#pragma warning(pop)
#endif// _MSC_VER

#if defined(HEXEN_WIN32_THREADS)
		// Temporarily set the main threads ID to -1, so when the worker threads start up, they don't accidentally use it
		// I don't know if Windows threads id's can ever be 0, but just in case.
		threads[0].Id = static_cast<DWORD>(-1);
#endif

		if (callbacks.onThreadsCreated != nullptr)
		{
			callbacks.onThreadsCreated(callbacks.context, numberOfThreads);
		}
		if (callbacks.onFibersCreated != nullptr)
		{
			callbacks.onFibersCreated(callbacks.context, options.fiberPoolSize);
		}

		// Set the properties for the current threads
		thread::setCurrentThreadAffinity(0);
		threads[0] = thread::getCurrentThread();
#if defined(HEXEN_WIN32_THREADS)
		// Set the threads handle to INVALID_HANDLE_VALUE
		// ::GetCurrentThread is a pseudo handle, that always references the current threads.
		// Aka, if we tried to use this handle from another threads to reference the main threads,
		// it would instead reference the other threads. We don't currently use the handle anywhere.
		// Therefore, we set this to INVALID_HANDLE_VALUE, so any future usages can take this into account
		// Reported by @rtj
		threads[0].Handle = INVALID_HANDLE_VALUE;
#endif

		// Set the fiber index
		threadLocalStorage[0].currentFiberIndex = 0;

		// Create the worker threads
		for (auto i = 1; i < numberOfThreads; ++i)
		{
			auto *const threadArgs = new ThreadStartArgs();
			threadArgs->scheduler = this;
			threadArgs->threadIndex = i;

			char threadName[256];
			snprintf(threadName, sizeof(threadName), "FTL Worker Thread %u", i);

			if (!thread::createThread(524288, threadStartFunction, threadArgs, threadName, &threads[i]))
			{
				return initErrorFailedToCreateWorkerThread;
			}
		}

		// Manually invoke callback for 'main' fiber
		if (callbacks.onFiberAttached != nullptr)
		{
			callbacks.onFiberAttached(callbacks.context, 0);
		}

		// Signal the worker threads that we're fully initialized
		isInitialized.store(true, std::memory_order_release);

		return 0;
	}

	TaskScheduler::~TaskScheduler()
	{
		// Create the quit fibers
		quitFibers = new Fiber[numberOfThreads];
		for (u32 i = 0; i < numberOfThreads; ++i)
		{
			quitFibers[i] = Fiber(524288, threadEndFunction, this);
		}

		// Request that all the threads quit
		isQuit.store(true, std::memory_order_release);

		// Signal any waiting threads so they can finish
		if (emptyQueueBehavior.load(std::memory_order_relaxed) == EmptyQueueBehavior::Sleep)
		{
			threadSleepCv.notify_all();
		}

		// Jump to the quit fiber
		// Create a scope so index isn't used after we come back from the switch. It will be wrong if we started on a non-main threads
		{
			if (callbacks.onFiberDetached != nullptr)
			{
				callbacks.onFiberDetached(callbacks.context, getCurrentFiberIndex(), false);
			}

			unsigned index = getCurrentThreadIndex();
			fibers[threadLocalStorage[index].currentFiberIndex].switchToFiber(&quitFibers[index]);
		}

		// We're back. We should be on the main threads now

		// Wait for the worker threads to finish
		for (unsigned i = 1; i < numberOfThreads; ++i)
		{
			thread::joinThread(threads[i]);
		}

		// Cleanup
		delete[] threadLocalStorage;
		delete[] threads;
		delete[] readyFiberBundles;
		delete[] freeFibers;
		delete[] fibers;

		delete[] quitFibers;
	}

	void TaskScheduler::addTask(const Task &task, TaskPriority priority, TaskCounter *counter)
	{
		HEXEN_ASSERT(task.delegate != nullptr, "Task given to TaskScheduler:addTask has a nullptr Function");

		if (counter != nullptr)
		{
			counter->add(1);
		}

		const TaskBundle bundle = {task, counter};
		if (priority == TaskPriority::High)
		{
			threadLocalStorage[getCurrentThreadIndex()].highPriorityTaskQueue.push(bundle);
		}
		else if (priority == TaskPriority::Normal)
		{
			threadLocalStorage[getCurrentThreadIndex()].normalPriorityTaskQueue.push(bundle);
		}

		const EmptyQueueBehavior behavior = emptyQueueBehavior.load(std::memory_order_relaxed);
		if (behavior == EmptyQueueBehavior::Sleep)
		{
			// Wake a sleeping threads
			threadSleepCv.notify_one();
		}
	}

	void TaskScheduler::addTasks(const std::array<Task, 400> &tasks, TaskPriority priority, TaskCounter *counter)
	{
		if (counter != nullptr)
		{
			counter->add(tasks.size());
		}

		WaitFreeQueue<TaskBundle> *queue = nullptr;
		if (priority == TaskPriority::High)
		{
			queue = &threadLocalStorage[getCurrentThreadIndex()].highPriorityTaskQueue;
		}
		else if (priority == TaskPriority::Normal)
		{
			queue = &threadLocalStorage[getCurrentThreadIndex()].normalPriorityTaskQueue;
		}
		else
		{
			HEXEN_ASSERT(false, "Unknown task priority");
			return;
		}
		for (u32 i = 0; i < tasks.size(); ++i)
		{
			HEXEN_ASSERT(tasks[i].delegate != nullptr, "Task given to TaskScheduler:addTasks has a nullptr Function");
			const TaskBundle bundle = {tasks[i], counter};
			queue->push(bundle);
		}

		const EmptyQueueBehavior behavior = emptyQueueBehavior.load(std::memory_order_relaxed);
		if (behavior == EmptyQueueBehavior::Sleep)
		{
			// Wake all the threads
			threadSleepCv.notify_all();
		}
	}

#if defined(HEXEN_WIN32_THREADS)

	HEXEN_NOINLINE u32 TaskScheduler::getCurrentThreadIndex() const
	{
		DWORD const threadId = ::GetCurrentThreadId();
		for (unsigned i = 0; i < numberOfThreads; ++i)
		{
			if (threads[i].Id == threadId)
			{
				return i;
			}
		}

		return invalidIndex;
	}

#elif defined(HEXEN_POSIX_THREADS)

	HEXEN_NOINLINE u32 TaskScheduler::getCurrentThreadIndex() const
	{
		pthread_t const currentThread = pthread_self();
		for (unsigned i = 0; i < numberOfThreads; ++i)
		{
			if (pthread_equal(currentThread, threads[i]) != 0)
			{
				return i;
			}
		}

		return invalidIndex;
	}

#endif

	unsigned TaskScheduler::getCurrentFiberIndex() const
	{
		auto &tls = threadLocalStorage[getCurrentThreadIndex()];
		return tls.currentFiberIndex;
	}

	inline bool TaskScheduler::taskIsReadyToExecute(TaskBundle *bundle) const
	{
		// "Real" tasks are always ready to execute
		if (bundle->taskToExecute != &ReadyFiberDummyTask)
		{
			return true;
		}

		// If it's a ready fiber task, the arg is a ReadyFiberBundle
		auto *readyFiberBundle = reinterpret_cast<ReadyFiberBundle *>(bundle->taskToExecute.ArgumentsData);
		return readyFiberBundle->fiberIsSwitched.load(std::memory_order_acquire);
	}

	bool TaskScheduler::getNextHighPriorityTask(TaskBundle *nextTask, std::vector<TaskBundle> *taskBuffer)
	{
		auto const currentThreadIndex = getCurrentThreadIndex();
		auto &tls = threadLocalStorage[currentThreadIndex];

		bool result = false;

		// Try to pop from our own queue
		while (tls.highPriorityTaskQueue.pop(nextTask))
		{
			if (taskIsReadyToExecute(nextTask))
			{
				result = true;
				cleanup(tls, taskBuffer);
				break;
			}

			// It's a ReadyTask whose fiber hasn't switched away yet
			// Add it to the buffer
			taskBuffer->emplace_back(*nextTask);
		}

		// Force a scope so the `goto cleanup` above doesn't skip initialization
		{
			// Ours is empty, try to steal from the others'
			const auto threadIndex = tls.higPriorityLastSuccessfulSteal;
			for (unsigned i = 0; i < numberOfThreads; ++i)
			{
				const auto threadIndexToStealFrom = (threadIndex + i) % numberOfThreads;
				if (threadIndexToStealFrom == currentThreadIndex)
				{
					continue;
				}
				auto &otherTLS = threadLocalStorage[threadIndexToStealFrom];

				while (otherTLS.highPriorityTaskQueue.steal(nextTask))
				{
					tls.higPriorityLastSuccessfulSteal = threadIndexToStealFrom;

					if (taskIsReadyToExecute(nextTask))
					{
						result = true;
						// Break to cleanup
						cleanup(tls, taskBuffer);
						break;
					}

					// It's a ReadyTask whose fiber hasn't switched away yet
					// Add it to the buffer
					taskBuffer->emplace_back(*nextTask);
				}
			}
		}

	cleanup:


		return result;
	}

	bool TaskScheduler::getNextNormalPriorityTask(TaskBundle *nextTask)
	{
		auto const currentThreadIndex = getCurrentThreadIndex();
		auto &tls = threadLocalStorage[currentThreadIndex];

		// Try to pop from our own queue
		if (tls.normalPriorityTaskQueue.pop(nextTask))
		{
			return true;
		}

		// Ours is empty, try to steal from the others'
		const auto threadIndex = tls.normalPriorityLastSuccessfulSteal;
		for (unsigned i = 0; i < numberOfThreads; ++i)
		{
			const auto threadIndexToStealFrom = (threadIndex + i) % numberOfThreads;
			if (threadIndexToStealFrom == currentThreadIndex)
			{
				continue;
			}
			auto &otherTLS = threadLocalStorage[threadIndexToStealFrom];
			if (otherTLS.normalPriorityTaskQueue.steal(nextTask))
			{
				tls.normalPriorityLastSuccessfulSteal = threadIndexToStealFrom;
				return true;
			}
		}

		return false;
	}

	unsigned TaskScheduler::getNextFreeFiberIndex() const
	{
		for (unsigned j = 0;; ++j)
		{
			for (unsigned i = 0; i < fiberPoolSize; ++i)
			{
				// Double lock
				if (!freeFibers[i].load(std::memory_order_relaxed))
				{
					continue;
				}

				if (!freeFibers[i].load(std::memory_order_acquire))
				{
					continue;
				}

				bool expected = true;
				if (std::atomic_compare_exchange_weak_explicit(&freeFibers[i], &expected, false, std::memory_order_release, std::memory_order_relaxed))
				{
					return i;
				}
			}

			if (j > 10)
			{
				printf("No free fibers in the pool. Possible deadlock");
			}
		}
	}

	void TaskScheduler::cleanUpOldFiber()
	{
		// Clean up from the last Fiber to run on this threads
		//
		// Explanation:
		// When switching between fibers, there's the innate problem of tracking the fibers.
		// For example, let's say we discover a waiting fiber that's ready. We need to put the currently
		// running fiber back into the fiber pool, and then switch to the waiting fiber. However, we can't
		// just do the equivalent of:
		//     fibers.Push(currentFiber)
		//     currentFiber.SwitchToFiber(waitingFiber)
		// In the time between us adding the current fiber to the fiber pool and switching to the waiting fiber, another
		// threads could come along and pop the current fiber from the fiber pool and try to run it.
		// This leads to stack corruption and/or other undefined behavior.
		//
		// In the previous implementation of TaskScheduler, we used helper fibers to do this work for us.
		// AKA, we stored currentFiber and waitingFiber in TLS, and then switched to the helper fiber. The
		// helper fiber then did:
		//     fibers.Push(currentFiber)
		//     helperFiber.SwitchToFiber(waitingFiber)
		// If we have 1 helper fiber per threads, we can guarantee that currentFiber is free to be executed by any threads
		// once it is added back to the fiber pool
		//
		// This solution works well, however, we actually don't need the helper fibers
		// The code structure guarantees that between any two fiber switches, the code will always end up in waitForCounter
		// or FiberStart. Therefore, instead of using a helper fiber and immediately pushing the fiber to the fiber pool or
		// waiting list, we defer the push until the next fiber gets to one of those two places
		//
		// Proof:
		// There are only two places where we switch fibers:
		// 1. When we're waiting for a counter, we pull a new fiber from the fiber pool and switch to it.
		// 2. When we found a counter that's ready, we put the current fiber back in the fiber pool, and switch to the
		// waiting fiber.
		//
		// Case 1:
		// A fiber from the pool will always either be completely new or just come back from switching to a waiting fiber
		// In both places, we call cleanUpOldFiber()
		// QED
		//
		// Case 2:
		// A waiting fiber will always resume in waitForCounter()
		// Here, we call cleanUpOldFiber()
		// QED

		auto &tls = threadLocalStorage[getCurrentThreadIndex()];
		switch (tls.oldFiberDestination)
		{
			case FiberDestination::ToPool:
				// In this specific implementation, the fiber pool is a flat array signaled by atomics
				// So in order to "Push" the fiber to the fiber pool, we just set its corresponding atomic to true
				freeFibers[tls.oldFiberIndex].store(true, std::memory_order_release);
				tls.oldFiberDestination = FiberDestination::None;
				tls.oldFiberIndex = invalidIndex;
				break;
			case FiberDestination::ToWaiting:
				// The waiting fibers are stored directly in their counters
				// They have an atomic<bool> that signals whether the waiting fiber can be consumed if it's ready
				// We just have to set it to true
				tls.oldFiberStoredFlag->store(true, std::memory_order_release);
				tls.oldFiberDestination = FiberDestination::None;
				tls.oldFiberIndex = invalidIndex;
				break;
			case FiberDestination::None:
			default:
				break;
		}
	}

	void TaskScheduler::addReadyFiber(unsigned pinnedThreadIndex, ReadyFiberBundle *bundle)
	{
		if (pinnedThreadIndex == noThreadPinning)
		{
			auto *tls = &threadLocalStorage[getCurrentThreadIndex()];

			// Push a dummy task to the high priority queue
			Task task {};
			task.bind(&ReadyFiberDummyTask, this, (vptr) bundle);
			task.ArgumentsData = bundle;
			TaskBundle taskBundle {};
			taskBundle.taskToExecute = task;
			taskBundle.counter = nullptr;

			tls->highPriorityTaskQueue.push(taskBundle);

			// If we're using EmptyQueueBehavior::Sleep, the other threads could be sleeping
			// Therefore, we need to kick a threads awake to ensure that the readied task is taken
			const auto behavior = emptyQueueBehavior.load(std::memory_order_relaxed);
			if (behavior == EmptyQueueBehavior::Sleep)
			{
				threadSleepCv.notify_one();
			}
		}
		else
		{
			auto *tls = &threadLocalStorage[pinnedThreadIndex];

			{
				std::lock_guard<std::mutex> guard(tls->pinnedReadyFibersLock);
				tls->pinnedReadyFibers.emplace_back(bundle);
			}

			// If the Task is pinned, we add the Task to the pinned threads's pinnedReadyFibers queue
			// Normally, this works fine; the other threads will pick it up next time it
			// searches for a Task to run.
			//
			// However, if we're using EmptyQueueBehavior::Sleep, the other threads could be sleeping
			// Therefore, we need to kick all the threads so that the pinned-to threads can take it
			const auto behavior = emptyQueueBehavior.load(std::memory_order::memory_order_relaxed);
			if (behavior == EmptyQueueBehavior::Sleep)
			{
				if (getCurrentThreadIndex() != pinnedThreadIndex)
				{
					std::unique_lock<std::mutex> lock(threadSleepLock);
					// Kick all threads
					threadSleepCv.notify_all();
				}
			}
		}
	}

	void TaskScheduler::waitForCounter(TaskCounter *counter, bool pinToCurrentThread)
	{
		waitForCounterInternal(counter, 0, pinToCurrentThread);
	}

	void TaskScheduler::waitForCounter(AtomicFlag *counter, bool pinToCurrentThread)
	{
		waitForCounterInternal(counter, 0, pinToCurrentThread);
	}

	void TaskScheduler::waitForCounter(FullAtomicCounter *counter, u32 value, bool pinToCurrentThread)
	{
		waitForCounterInternal(counter, value, pinToCurrentThread);
	}

	void TaskScheduler::waitForCounterInternal(BaseCounter *counter, u32 value, bool pinToCurrentThread)
	{
		// Fast out
		if (counter->value.load(std::memory_order_relaxed) == value)
		{
			// wait for threads to drain from counter logic, otherwise we might continue too early
			while (counter->lock.load() > 0)
			{
			}
			return;
		}

		auto &tls = threadLocalStorage[getCurrentThreadIndex()];
		auto const currentFiberIndex = tls.currentFiberIndex;

		u32 pinnedThreadIndex;
		if (pinToCurrentThread)
		{
			pinnedThreadIndex = getCurrentThreadIndex();
		}
		else
		{
			pinnedThreadIndex = noThreadPinning;
		}

		// Create the ready fiber bundle and attempt to add it to the waiting list
		ReadyFiberBundle *readyFiberBundle = &readyFiberBundles[currentFiberIndex];
		readyFiberBundle->fiberIndex = currentFiberIndex;
		readyFiberBundle->fiberIsSwitched.store(false);

		auto const alreadyDone = counter->addFiberToWaitingList(readyFiberBundle, value, pinnedThreadIndex);

		// The counter finished while we were trying to put it in the waiting list
		// Just trivially return
		if (alreadyDone)
		{
			return;
		}

		// Get a free fiber
		auto const freeFiberIndex = getNextFreeFiberIndex();

		// Fill in tls
		tls.oldFiberIndex = currentFiberIndex;
		tls.currentFiberIndex = freeFiberIndex;
		tls.oldFiberDestination = FiberDestination::ToWaiting;
		tls.oldFiberStoredFlag = &readyFiberBundle->fiberIsSwitched;

		if (callbacks.onFiberDetached != nullptr)
		{
			callbacks.onFiberDetached(callbacks.context, currentFiberIndex, true);
		}

		// Switch
		fibers[currentFiberIndex].switchToFiber(&fibers[freeFiberIndex]);

		if (callbacks.onFiberAttached != nullptr)
		{
			callbacks.onFiberAttached(callbacks.context, getCurrentFiberIndex());
		}

		// And we're back
		cleanUpOldFiber();
	}

	void TaskScheduler::cleanup(TaskScheduler::ThreadLocalStorage &tls, std::vector<TaskBundle> *taskBuffer)
	{
		if (!taskBuffer->empty())
		{
			// Re-push all the tasks we found that we're ready to execute
			// We (or another threads) will get them next round
			do
			{
				// Push them in the opposite order we popped them, to restore the order
				tls.highPriorityTaskQueue.push(taskBuffer->back());
				taskBuffer->pop_back();
			} while (!taskBuffer->empty());

			// If we're using Sleep mode, we need to wake up the other threads
			// They may have looked for tasks while we had them all in our temp buffer and thus not
			// found anything and gone to sleep.
			EmptyQueueBehavior const behavior = emptyQueueBehavior.load(std::memory_order::memory_order_relaxed);
			if (behavior == EmptyQueueBehavior::Sleep)
			{
				// Wake all the threads
				threadSleepCv.notify_all();
			}
		}
	}
}// namespace hexen::engine::core::threading

//
// Created by cx9ps3 on 14.07.2023.
//

#include "TaskManager.h"
#include "Thread.h"
#include "Fiber.h"
#include "TaskCounter.h"
#include <thread>
#include <sstream>

#if defined(WINDOWS_API)
#include <Windows.h>
#elif defined(POSIX_API)

#define _GNU_SOURCE

#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>

#endif

core::threading::TaskManager::TaskManager(const core::threading::TaskManagerOptions &options) : numberOfThreads(options.numberOfThreads) , isThreadAffinity(options.threadAffinity) , numberOfFibers(options.numberOfFibers) ,highPriorityQueue(options.highPriorityQueueSize) , normalPriorityQueue(options.normalPriorityQueueSize) , lowPriorityQueue(options.lowPriorityQueueSize) , shutdownAfterMain(options.isShutdownAfterMainCallback)
{

}

core::threading::TaskManager::~TaskManager()
{
    delete[] threads;
    delete[] fibers;
    delete[] idleFibers;
}

core::threading::TaskManager::ReturnCode core::threading::TaskManager::run(core::threading::TaskManager::MainCallback callback)
{
    if (threads != nullptr || fibers != nullptr)
    {
        return ReturnCode::AlreadyInitialized;
    }

    threads = new Thread[numberOfThreads];
    auto mainThread = &threads[0];

    mainThread->fromCurrentThread();

    if (isThreadAffinity)
    {
        mainThread->setAffinity(1);
    }

    auto mainThreadLocalStorage = mainThread->getStorage();
    mainThreadLocalStorage->threadFiber.convertFromCurrentThread();

    if (numberOfFibers == 0)
    {
        return ReturnCode::InvalidNumberOfFibers;
    }

    fibers = new Fiber[numberOfFibers];
    idleFibers = new std::atomic_bool[numberOfFibers];

    for (u32 i = 0; i < numberOfFibers; i++)
    {
        fibers[i].setCallback(fiberCallbackWorker);
        idleFibers[i].store(true, std::memory_order_relaxed);
    }

    if (isThreadAffinity && numberOfThreads > std::thread::hardware_concurrency())
    {
        return ReturnCode::ErrorThreadAffinity;
    }

    //Spawn threads
    for (u16 i = 0; i < numberOfThreads; i++)
    {

        auto storage = threads[i].getStorage();
        storage->threadIndex = i;

        if (i > 0)
        {
            storage->setAffinity = isThreadAffinity;

            if (!threads[i].spawn(threadCallbackWorker, this))
            {
                return ReturnCode::OSError;
            }
        }
    }

    if (callback == nullptr)
    {
        return ReturnCode::NullCallback;
    }

    mainCallback = callback;

    mainThreadLocalStorage->currentFiberIndex = findFreeFiber();
    auto mainFiber = &fibers[mainThreadLocalStorage->currentFiberIndex];
    mainFiber->setCallback(fiberCallbackMain);

    mainThreadLocalStorage->threadFiber.switchTo(mainFiber, this);

    for (u16 i = 1; i < numberOfThreads; i++)
    {
        threads[i].join();
    }

    return ReturnCode::Succes;
}

void core::threading::TaskManager::shutdown(bool isBlocking)
{
    isShuttingDown.store(true,std::memory_order_release);
    if(isBlocking)
    {
        for(u32 i = 1; i < numberOfFibers; i++)
        {
            threads[i].join();
        }
    }
}

core::u32 core::threading::TaskManager::findFreeFiber()
{
    while (true)
    {
        for (u32 i = 0; i < numberOfFibers; i++)
        {
            if (!idleFibers[i].load(std::memory_order_relaxed) || !idleFibers[i].load(std::memory_order_acquire))
            {
                continue;
            }

            bool expected = true;
            if (std::atomic_compare_exchange_weak_explicit(&idleFibers[i], &expected, false, std::memory_order_release, std::memory_order_relaxed))
            {
                return i;
            }
        }

    }
}

void core::threading::TaskManager::cleanupPreviousFiber(core::threading::ThreadLocalStorage *storage)
{
    if (storage == nullptr)
    {
        storage = getCurrentTLS();
    }

    switch (storage->previousFiberDestination)
    {
        case FiberDestination::None:
            return;

        case FiberDestination::Pool:
            idleFibers[storage->previousFiberIndex].store(true, std::memory_order_release);
            break;

        case FiberDestination::Waiting:
            storage->isPreviousFiberStored->store(true, std::memory_order_relaxed);
            break;

        default:
            break;
    }

    // Cleanup TLS
    storage->previousFiberIndex = UINT16_MAX;
    storage->previousFiberDestination = FiberDestination::None;
    storage->isPreviousFiberStored = nullptr;
}

void core::threading::TaskManager::threadCallbackWorker(core::threading::Thread *thread)
{
    auto manager = reinterpret_cast<core::threading::TaskManager*>(thread->getUserData());
    auto tls = thread->getStorage();

    // Thread Affinity
    if (tls->setAffinity)
    {
        thread->setAffinity(tls->threadIndex);
    }

    // Setup Thread Fiber
    tls->threadFiber.convertFromCurrentThread();

    // Fiber
    tls->currentFiberIndex = manager->findFreeFiber();

    auto fiber = &manager->fibers[tls->currentFiberIndex];
    tls->threadFiber.switchTo(fiber, manager);
}

void core::threading::TaskManager::fiberCallbackWorker(core::threading::Fiber *fiber)
{
    auto manager = reinterpret_cast<core::threading::TaskManager*>(fiber->getUserData());
    manager->cleanupPreviousFiber();

    TaskInfo task;

    while (!manager->isShuttingDown)
    {
        auto tls = manager->getCurrentTLS();

        if (manager->getNextTask(task, tls))
        {
            task.execute();
            continue;
        }

        Thread::sleepFor(1);
    }

    // Switch back to Thread
    fiber->switchBack();
}

void core::threading::TaskManager::fiberCallbackMain(core::threading::Fiber *fiber)
{
    auto manager = reinterpret_cast<core::threading::TaskManager*>(fiber->getUserData());

    // Main
    manager->mainCallback(manager);

    // Shutdown after Main
    if (!manager->shutdownAfterMain)
    {
        // Switch to idle Fiber
        auto tls = manager->getCurrentTLS();
        tls->currentFiberIndex = manager->findFreeFiber();

        auto fiber = &manager->fibers[tls->currentFiberIndex];
        tls->threadFiber.switchTo(fiber, manager);
    }

    // Shutdown
    manager->shutdown(false);

    // Switch back to Main Thread
    fiber->switchBack();
}

core::threading::detail::TaskQueue *core::threading::TaskManager::getQueueByPriority(core::threading::TaskPriority taskPriority)
{
    switch (taskPriority)
    {
        case TaskPriority::High:
            return &highPriorityQueue;
        case TaskPriority::Normal:
            return &normalPriorityQueue;
        case TaskPriority::Low:
            return &lowPriorityQueue;
        default:
            return nullptr;
    }
    return nullptr;
}

bool core::threading::TaskManager::getNextTask(core::threading::TaskInfo &taskInfo,core::threading::ThreadLocalStorage *storage)
{
    if(highPriorityQueue.dequeue(taskInfo))
    {
        return true;
    }

    if(storage == nullptr)
    {
        storage = getCurrentTLS();
    }

    for (auto it = storage->readyFibers.begin(); it != storage->readyFibers.end(); ++it)
    {
        uint16_t fiberIndex = it->first;

        // Make sure Fiber is stored
        if (!it->second->load(std::memory_order_relaxed))
            continue;

        // Erase
        delete it->second;
        storage->readyFibers.erase(it);

        // Update TLS
        storage->previousFiberIndex = storage->currentFiberIndex;
        storage->previousFiberDestination = FiberDestination::Pool;
        storage->currentFiberIndex = fiberIndex;

        // Switch to Fiber
        storage->threadFiber.switchTo(&fibers[fiberIndex], this);
        cleanupPreviousFiber(storage);

        break;
    }

    // Normal & Low Priority Jobs
    return normalPriorityQueue.dequeue(taskInfo) || lowPriorityQueue.dequeue(taskInfo);
}


void core::threading::TaskManager::scheduleTask(core::threading::TaskPriority taskPriority, const core::threading::TaskInfo &task)
{
    auto queue = getQueueByPriority(taskPriority);
    if (!queue)
    {
        return;
    }

    if (task.getCounter())
    {
        task.getCounter()->increment();
    }

    assert(queue->enqueue(task) && "Task queue is Full!");
}

void core::threading::TaskManager::waitForCounter(core::threading::detail::BaseCounter *counter, core::u32 value)
{
    if (counter == nullptr || counter->getValue() == value)
    {
        return;
    }

    auto tls = getCurrentTLS();
    auto fiberStored = new std::atomic_bool(false);

    if (counter->addWaitingFiber(tls->currentFiberIndex, value, fiberStored))
    {
        // Already done
        delete fiberStored;
        return;
    }

    // Update TLS
    tls->previousFiberIndex = tls->currentFiberIndex;
    tls->previousFiberDestination = FiberDestination::Waiting;
    tls->isPreviousFiberStored = fiberStored;

    // Switch to idle Fiber
    tls->currentFiberIndex = findFreeFiber();
    tls->threadFiber.switchTo(&fibers[tls->currentFiberIndex], this);

    // Cleanup
    cleanupPreviousFiber();
}

void core::threading::TaskManager::waitForSingle(core::threading::TaskPriority taskPriority, core::threading::TaskInfo task)
{
    detail::TinyCounter ctr(this);
    task.setCounter(&ctr);

    scheduleTask(taskPriority, task);
    waitForCounter(&ctr);
}

core::u16 core::threading::TaskManager::getCurrentThreadIndex() const
{

#if defined(WINDOWS_API)

    auto id = GetCurrentThreadId();

#elif defined(POSIX_API)

    auto id = pthread_self();

#endif

    for(u16 i = 0; i < numberOfThreads ; i++)
    {
        if(threads[i].getID() == id)
        {
            return i;
        }
    }

    return UINT16_MAX;
}

core::threading::Thread *core::threading::TaskManager::getCurrentThread() const
{

#if defined(WINDOWS_API)

    auto id = GetCurrentThreadId();

#elif defined(POSIX_API)

    auto id = pthread_self();

#endif

    for(u16 i = 0; i < numberOfThreads ; i++)
    {
        if(threads[i].getID() == id)
        {
            return &threads[i];
        }
    }

    return nullptr;
}

core::threading::ThreadLocalStorage *core::threading::TaskManager::getCurrentTLS() const
{
#if defined(WINDOWS_API)

    auto id = GetCurrentThreadId();

#elif defined(POSIX_API)

    auto id =  pthread_self();

#endif


    for(u16 i = 0; i < numberOfThreads ; i++)
    {
        if(threads[i].getID() == id)
        {
            return threads[i].getStorage();
        }
    }



    return nullptr;
}


#pragma once

#include "Callbacks.h"
#include "../threads/Fiber.h"
#include "Task.h"
#include "../threads/Thread.h"
#include "../threads/WaitFreeQueue.h"

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <array>

namespace core::threading
{
    class BaseCounter;
    class TaskCounter;
    class AtomicFlag;
    class FullAtomicCounter;

    enum class EmptyQueueBehavior
    {
        // Spin in a loop, actively searching for tasks
        Spin,
        // Same as spin, except yields to the OS after each round of searching
        Yield,
        // Puts the threads to sleep. Will be woken when more tasks are added to the remaining awake threads.
        Sleep
        // ReSharper restore CppInconsistentNaming
    };

    struct TaskSchedulerInitOptions
    {
        unsigned fiberPoolSize = 400;
        unsigned threadPoolSize = 0;
        EmptyQueueBehavior behavior = EmptyQueueBehavior::Spin;
        EventCallbacks callbacks;
    };

    class TaskScheduler
    {
    public:
        TaskScheduler() = default;

        TaskScheduler(TaskScheduler const &) = delete;
        TaskScheduler(TaskScheduler &&) noexcept = delete;
        TaskScheduler &operator=(TaskScheduler const &) = delete;
        TaskScheduler &operator=(TaskScheduler &&) noexcept = delete;
        ~TaskScheduler();

    private:

        enum class FiberDestination {
            None = 0,
            ToPool = 1,
            ToWaiting = 2,
        };

        struct TaskBundle
        {
            Task taskToExecute;
            TaskCounter *counter;
        };

        struct ReadyFiberBundle
        {
            ReadyFiberBundle() = default;
            u32 fiberIndex;
            std::atomic<bool> fiberIsSwitched;
        };

        struct alignas(cacheLineSize) ThreadLocalStorage
        {
            ThreadLocalStorage(): currentFiberIndex(invalidIndex), oldFiberIndex(invalidIndex) {}

        public:

            WaitFreeQueue<TaskBundle> highPriorityTaskQueue;
            WaitFreeQueue<TaskBundle> normalPriorityTaskQueue;

            std::atomic<bool> *oldFiberStoredFlag{nullptr};

            std::vector<ReadyFiberBundle *> pinnedReadyFibers;

            Fiber threadFiber;

            std::mutex pinnedReadyFibersLock;

            u32 currentFiberIndex;

            u32 oldFiberIndex;

            FiberDestination oldFiberDestination{FiberDestination::None};

            u32 higPriorityLastSuccessfulSteal{1};
            u32 normalPriorityLastSuccessfulSteal{1};

            u32 failedQueuePopAttempts{0};
        };

    private:
        // Member variables

        constexpr static unsigned invalidIndex = std::numeric_limits<u32>::max();
        constexpr static unsigned noThreadPinning = std::numeric_limits<u32>::max();

        EventCallbacks callbacks;

        u32 numberOfThreads{0};
        thread::ThreadType *threads{nullptr};

        u32 fiberPoolSize{0};

        Fiber *fibers{nullptr};

        std::atomic<bool> *freeFibers{nullptr};

        ReadyFiberBundle *readyFiberBundles{nullptr};

        Fiber *quitFibers{nullptr};

        std::atomic<bool> isInitialized{false};
        std::atomic<bool> isQuit{false};
        std::atomic<unsigned> quitCount{0};

        std::atomic<EmptyQueueBehavior> emptyQueueBehavior{EmptyQueueBehavior::Spin};

        std::mutex threadSleepLock;
        std::condition_variable threadSleepCv;

        ThreadLocalStorage *threadLocalStorage{nullptr};

        friend class BaseCounter;

    public:

        int initialize(TaskSchedulerInitOptions options = TaskSchedulerInitOptions());

        void addTask(Task task, TaskPriority priority, TaskCounter *counter = nullptr);

        void addTasks(const std::array<Task,400> &tasks, TaskPriority priority, TaskCounter *counter = nullptr);

        void waitForCounter(TaskCounter *counter, bool pinToCurrentThread = false);

        void waitForCounter(AtomicFlag *counter, bool pinToCurrentThread = false);

        void waitForCounter(FullAtomicCounter *counter, u32 value, bool pinToCurrentThread = false);


        HEXEN_NOINLINE u32 getCurrentThreadIndex() const;


        u32 getCurrentFiberIndex() const;

        u32 getThreadCount() const noexcept
        {
            return numberOfThreads;
        }

        u32 getFiberCount() const noexcept
        {
            return fiberPoolSize;
        }

        void setEmptyQueueBehavior(EmptyQueueBehavior const behavior)
        {
            emptyQueueBehavior.store(behavior, std::memory_order_relaxed);
        }

    private:
        void cleanup(ThreadLocalStorage &tls, std::vector<TaskBundle> *taskBuffer);

        bool getNextHighPriorityTask(TaskBundle *nextTask, std::vector<TaskBundle> *taskBuffer);

        bool getNextNormalPriorityTask(TaskBundle *nextTask);

        bool taskIsReadyToExecute(TaskBundle *bundle) const;

        u32 getNextFreeFiberIndex() const;

        void cleanUpOldFiber();

        void waitForCounterInternal(BaseCounter *counter, u32 value, bool pinToCurrentThread);


        void addReadyFiber(u32 pinnedThreadIndex, ReadyFiberBundle *bundle);

        static HEXEN_THREAD_FUNC_DECL threadStartFunction(vptr arg);

        static void fiberStartFunction(vptr arg);

        static void threadEndFunction(vptr arg);
    };

}

//
// Created by cx9ps3 on 14.07.2023.
//

#pragma once

#include "../Types.h"
#include "Config.h"
#include "Task.h"
#include "detail/WaitFreeQueue.h"
#include "Fiber.h"
#include "Thread.h"

#include <condition_variable>
#include <functional>


namespace core::threading
{
    class Thread;
    class AtomicFlag;
    class AtomicCounter;
    class BaseCounter;
    class Fiber;


    enum class EmptyQueueBehavior : u8
    {
        Spin,
        Yield,
        Sleep,
    };

    struct TaskManagerOptions
    {
        TaskManagerOptions() : numberOfThreads(std::thread::hardware_concurrency()){}
        ~TaskManagerOptions() = default;

        u32 numberOfThreads;
        u32 fiberPoolSize{400};

        bool threadAffinity{true};

        EmptyQueueBehavior behavior = EmptyQueueBehavior::Spin;

        u64 highPriorityQueueSize  {512};
        u64 normalPriorityQueueSize {2048};
        u64 lowPriorityQueueSize {4096};

        bool isShutdownAfterMainCallback{true};
    };

    class TaskManager
    {

    private:

        enum class FiberDestination : u8
        {
            None = 0,
            ToPool = 1,
            ToWaiting = 2,
        };

        struct TaskBundle
        {
            TaskInfo task;
            TaskCounter *counter;
        };

        struct ReadyFiberBundle
        {
            ReadyFiberBundle() = default;

            u32 fiberIndex;

            std::atomic<bool> fiberIsSwitched;

        };


        constexpr static auto invalidIndex = std::numeric_limits<u32>::max();
        constexpr static auto noThreadPinning = std::numeric_limits<u32>::max();

        struct alignas(cacheLineSize) ThreadLocalStorage
        {
            ThreadLocalStorage() : currentFiberIndex(invalidIndex) , oldFiberIndex(invalidIndex) {};

        public:


            detail::WaitFreeQueue<TaskBundle> highPriorityQueue;
            detail::WaitFreeQueue<TaskBundle> normalPriorityQueue;
            detail::WaitFreeQueue<TaskBundle> lowPriorityQueue;


            std::atomic<bool> *oldFiberStoredFlag{nullptr};

            std::vector<ReadyFiberBundle *> pinnedReadyFibers;
            Fiber threadFiber;
            std::mutex pinnedReadyFibersLock;

            u32 currentFiberIndex;
            u32 oldFiberIndex;

            FiberDestination oldFiberDestination{FiberDestination::None};

            u32 highPriorityLastSuccessfulSteal{1};

            u32 normalPriorityLastSuccessfulSteal{1};

            u32 lowPriorityLastSuccessfulSteal{1};

            u32 failedQueuePopAttempts{0};
        };

        u32 numberOfThreads{0};
        Thread *threads{nullptr};

        u32 fiberPoolSize{0};

        std::atomic<bool> *freeFibers{nullptr};

        ReadyFiberBundle *readyFiberBundles{nullptr};
        Fiber *quitFibers{nullptr};

        std::atomic<bool> isInitialized{false};

        std::atomic<bool> isQuit{false};

        std::atomic<u32> quitCount{0};

        std::atomic<EmptyQueueBehavior> emptyQueueBehavior{EmptyQueueBehavior::Spin};


        std::mutex threadLockSleep;
        std::condition_variable isThreadsSleep;

        ThreadLocalStorage *tls {nullptr};

        friend class BaseCounter;

        bool getNextHighProrityTask(TaskBundle *nextTask , std::vector<TaskBundle> *taskBuffer);

        bool getNextNormalProrityTask(TaskBundle *nextTask , std::vector<TaskBundle> *taskBuffer);

        bool getLowHighProrityTask(TaskBundle *nextTask , std::vector<TaskBundle> *taskBuffer);

        bool taskIsReadyToReady(TaskBundle *bundle) const;

        u32 getNextFreeFiberIndex() const;


        void cleanUpOldFiber();

        void waitForCounterInternal(BaseCounter *counter,u32 value ,bool pinToCurrentThread);

        void addReadyFiber(u32 pinnedThreadIndex,ReadyFiberBundle *bundle);

        static  HEXEN_THREAD_FUNC_DECL threadStartFunction(vptr args);

        static void fiberStartFunction(vptr args);

        static void threadEndFunction(vptr args);

    public:
        enum class ReturnCode : u8
        {
            Succes = 0,
            AlreadyInitialized,
            ErrorThreadAffinity,
        };

        explicit TaskManager(const TaskManagerOptions &options = TaskManagerOptions());

        TaskManager(TaskManager const &) = delete;
        TaskManager(TaskManager &&) noexcept = delete;
        TaskManager &operator=(TaskManager const &) = delete;
        TaskManager &operator=(TaskManager &&) noexcept = delete;

        ~TaskManager();

        ReturnCode initialize(const TaskManagerOptions& options = TaskManagerOptions());




        void scheduleTask(TaskPriority taskPriority , const TaskInfo &task,TaskCounter *taskCounter = nullptr);


        void waitForCounter(TaskCounter *counter , bool pinToCurrentThread = false);

        void waitForCounter(AtomicCounter *counter , u32 value = 0 , bool pinToCurrentThread = false);

        void waitForCounter(AtomicFlag *counter , u32 value = 0 , bool pinToCurrentThread = false);


        void waitForCounter(TaskCounter *counter , u32 value = 0 , bool pinToCurrentThread = false);

        HEXEN_NOINLINE u32 getCurrrentThreadIndex() const;

        u32 getCurrrentFiberIndex() const;

        u32 getNumberOfThreads() const noexcept
        {
            return numberOfThreads;
        }

        u32 getNumberOfFibers() const noexcept
        {
            return fiberPoolSize;
        }

        void setEmptyQueueBehavior(EmptyQueueBehavior behavior)
        {
            emptyQueueBehavior.store(behavior,std::memory_order_relaxed);
        }

        template <typename Callable, typename... Args>
        inline void scheduleTask(TaskPriority taskPriority, Callable callable, Args... args)
        {
            scheduleTask(taskPriority, TaskInfo(callable, args...));
        }

        template <typename Callable, typename... Args>
        inline void scheduleTask(TaskPriority taskPriority, const std::shared_ptr<TaskCounter> &ctr, Callable callable, Args... args)
        {
            scheduleTask(taskPriority, TaskInfo(ctr, callable, args...));
        }

        template <typename Callable, typename... Args>
        inline void waitForSingle(TaskPriority taskPriority, Callable callable, Args... args)
        {
            waitForSingle(taskPriority, TaskInfo(callable, args...));
        }


    };
}


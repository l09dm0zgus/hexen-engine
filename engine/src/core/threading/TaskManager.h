//
// Created by cx9ps3 on 14.07.2023.
//

#ifndef HEXENEDITOR_TASKMANAGER_H
#define HEXENEDITOR_TASKMANAGER_H
#include "../Types.h"
#include "Task.h"
#include <thread>

namespace core::threading
{
    class Thread;
    struct ThreadLocalStorage;
    class Fiber;

    class TaskCounter;
    namespace detail{ class BaseCounter; }

    struct TaskManagerOptions
    {
        TaskManagerOptions() : numberOfThreads(std::thread::hardware_concurrency()){}
        ~TaskManagerOptions() = default;

        u16 numberOfThreads;
        u32 numberOfFibers{160};

        bool threadAffinity{true};

        u64 highPriorityQueueSize  {512};
        u64 normalPriorityQueueSize {2048};
        u64 lowPriorityQueueSize {4096};

        bool isShutdownAfterMainCallback{true};
    };

    class TaskManager
    {
        friend class detail::BaseCounter;
    protected:
        std::atomic_bool  isShuttingDown{false};


        u16 numberOfThreads{0};
        Thread* threads{nullptr};
        bool isThreadAffinity{true};

        u32 numberOfFibers{0};
        Fiber *fibers{nullptr};
        std::atomic_bool* idleFibers{nullptr};

        u32 findFreeFiber();

        void cleanupPreviousFiber(ThreadLocalStorage *storage = nullptr);

        u16 getCurrentThreadIndex() const;
        Thread* getCurrentThread() const;
        ThreadLocalStorage* getCurrentTLS() const;

        detail::TaskQueue highPriorityQueue;
        detail::TaskQueue normalPriorityQueue;
        detail::TaskQueue lowPriorityQueue;

        detail::TaskQueue* getQueueByPriority(TaskPriority taskPriority);
        bool getNextTask(TaskInfo& taskInfo, ThreadLocalStorage* storage);


    public:
        enum class ReturnCode : u8
        {
            Succes = 0,
            UnknownError,
            OSError,
            NullCallback,
            AlreadyInitialized,
            InvalidNumberOfFibers,
            ErrorThreadAffinity,
        };

        using MainCallback = void(*)(TaskManager*);

        explicit TaskManager(const TaskManagerOptions &options = TaskManagerOptions());
        ~TaskManager();

        ReturnCode run(MainCallback callback);

        void shutdown(bool isBlocking);

        void scheduleTask(TaskPriority taskPriority , const TaskInfo &task);

        void waitForCounter(detail::BaseCounter* counter , u32 value = 0);
        void waitForSingle(TaskPriority taskPriority , TaskInfo task);

        template <typename Callable, typename... Args>
        inline void scheduleTask(TaskPriority taskPriority, Callable callable, Args... args)
        {
            scheduleTask(taskPriority, TaskInfo(callable, args...));
        }

        template <typename Callable, typename... Args>
        inline void scheduleTask(TaskPriority taskPriority, detail::BaseCounter* ctr, Callable callable, Args... args)
        {
            scheduleTask(taskPriority, TaskInfo(ctr, callable, args...));
        }

        template <typename Callable, typename... Args>
        inline void waitForSingle(TaskPriority taskPriority, Callable callable, Args... args)
        {
            waitForSingle(taskPriority, TaskInfo(callable, args...));
        }


    private:
        MainCallback mainCallback{nullptr};
        bool shutdownAfterMain{true};

        static void threadCallbackWorker(Thread *thread);
        static void fiberCallbackWorker(Fiber *fiber);
        static void fiberCallbackMain(Fiber *fiber);

    };
}




#endif //HEXENEDITOR_TASKMANAGER_H

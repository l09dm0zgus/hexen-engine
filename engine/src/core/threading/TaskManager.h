//
// Created by cx9ps3 on 14.07.2023.
//

#ifndef HEXENEDITOR_TASKMANAGER_H
#define HEXENEDITOR_TASKMANAGER_H
#include "../Types.h"
#include "Task.h"
#include <thread>
#include <boost/fiber/buffered_channel.hpp>
#include <condition_variable>
#include <functional>


namespace core::threading
{
    class Thread;
    class TaskCounter;

    struct TaskManagerOptions
    {
        TaskManagerOptions() : numberOfThreads(std::thread::hardware_concurrency()){}
        ~TaskManagerOptions() = default;

        u16 numberOfThreads;
        u32 numberOfFibers{15};

        bool threadAffinity{true};

        u64 highPriorityQueueSize  {512};
        u64 normalPriorityQueueSize {2048};
        u64 lowPriorityQueueSize {4096};

        bool isShutdownAfterMainCallback{true};
    };

    class TaskManager
    {

    private:
        std::atomic_bool  bIsShuttingDown{false};

        std::condition_variable waitingCounter;
        std::mutex waitingMutex;
        Thread* threads{nullptr};

        u16 numberOfThreads{0};

        bool isThreadAffinity{true};

        u32 numberOfFibers{0};


        std::shared_ptr<boost::fibers::buffered_channel<TaskInfo>> highPriorityQueue;
        std::shared_ptr<boost::fibers::buffered_channel<TaskInfo>> normalPriorityQueue;
        std::shared_ptr<boost::fibers::buffered_channel<TaskInfo>> lowPriorityQueue;

        std::shared_ptr<boost::fibers::buffered_channel<TaskInfo>>  getQueueByPriority(TaskPriority taskPriority);

    public:
        enum class ReturnCode : u8
        {
            Succes = 0,
            AlreadyInitialized,
            ErrorThreadAffinity,
        };

        explicit TaskManager(const TaskManagerOptions &options = TaskManagerOptions());

        ~TaskManager();

        ReturnCode initialize();

        void shutdown(bool isBlocking);

        void scheduleTask(TaskPriority taskPriority , const TaskInfo &task);

        void waitForCounter(const std::shared_ptr<TaskCounter> &counter , u32 value = 0);

        inline bool isShuttingDown() const { return bIsShuttingDown.load(std::memory_order_acquire); };
        const u16 getNumberOfThreads() const { return numberOfThreads; };
        const u32 getNumberOfFibers() const { return numberOfFibers; };


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


    private:
        bool shutdownAfterMain{true};


    };
}




#endif //HEXENEDITOR_TASKMANAGER_H

//
// Created by cx9ps3 on 14.07.2023.
//

#include "TaskManager.h"
#include "Thread.h"
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

core::threading::TaskManager::TaskManager(const core::threading::TaskManagerOptions &options) : numberOfThreads(options.numberOfThreads) , isThreadAffinity(options.threadAffinity) , numberOfFibers(options.numberOfFibers)  , shutdownAfterMain(options.isShutdownAfterMainCallback)
{
    highPriorityQueue  = std::make_shared<boost::fibers::buffered_channel<TaskInfo>>(options.highPriorityQueueSize);
    normalPriorityQueue  = std::make_shared<boost::fibers::buffered_channel<TaskInfo>>(options.normalPriorityQueueSize);
    lowPriorityQueue  = std::make_shared<boost::fibers::buffered_channel<TaskInfo>>(options.lowPriorityQueueSize);

}

core::threading::TaskManager::ReturnCode core::threading::TaskManager::initialize()
{
    if (threads != nullptr)
    {
        return ReturnCode::AlreadyInitialized;
    }

    threads = new Thread[numberOfThreads];

    if (isThreadAffinity && numberOfThreads > std::thread::hardware_concurrency())
    {
        return ReturnCode::ErrorThreadAffinity;
    }

    Thread::ThreadData data;

    data.numberOfFibers = numberOfFibers;
    data.highPriorityTasks = highPriorityQueue;
    data.normalPriorityTasks = normalPriorityQueue;
    data.lowPriorityTasks = lowPriorityQueue;

    //Spawn threads
    for (u16 i = 0; i < numberOfThreads; i++)
    {

        threads[i].setAffinity(i);
        threads[i].spawn(data);

    }

    for (u16 i = 0; i < numberOfThreads; i++)
    {
        threads[i].join();
    }

    return ReturnCode::Succes;
}

void core::threading::TaskManager::shutdown(bool isBlocking)
{
    bIsShuttingDown.store(true,std::memory_order_release);
    highPriorityQueue->close();
    normalPriorityQueue->close();
    lowPriorityQueue->close();
    if(isBlocking)
    {
        for(u32 i = 0; i < numberOfFibers; i++)
        {
            threads[i].join();
        }
    }
}


std::shared_ptr<boost::fibers::buffered_channel<core::threading::TaskInfo>> core::threading::TaskManager::getQueueByPriority(core::threading::TaskPriority taskPriority)
{
    switch (taskPriority)
    {
        case TaskPriority::High:
            return highPriorityQueue;
        case TaskPriority::Normal:
            return normalPriorityQueue;
        case TaskPriority::Low:
            return lowPriorityQueue;
        default:
            return nullptr;
    }
    return nullptr;
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
    if(!queue->is_closed())
    {
        queue->try_push(task);
    }
    std::cout << "Added task\n";
}

void core::threading::TaskManager::waitForCounter(const std::shared_ptr<TaskCounter> &counter, core::u32 value)
{
    while (counter->getValue() != value)
    {
        std::cout << "Waiting...Active tasks: " << counter->getValue() << "\n";
        if (counter == nullptr || counter->getValue() == value)
        {
            shutdown(false);
            return;
        }
    }
}

core::threading::TaskManager::~TaskManager()
{
    delete[] threads;
}



//
// Created by cx9ps3 on 13.07.2023.
//

#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include "Task.h"
#include <boost/fiber/buffered_channel.hpp>

namespace core::threading
{
    class Thread
    {
    public:

        struct ThreadData
        {
            u32 numberOfFibers{25};
            std::shared_ptr<boost::fibers::buffered_channel<TaskInfo>> highPriorityTasks;
            std::shared_ptr<boost::fibers::buffered_channel<TaskInfo>> normalPriorityTasks;
            std::shared_ptr<boost::fibers::buffered_channel<TaskInfo>> lowPriorityTasks;
        };

    private:
        std::thread::id id{0};

        explicit Thread(const std::thread::id &newID)
        {
            id = newID;
        }

        std::thread cppThread;
        ThreadData threadData;

    public:
        Thread() = default;
        Thread(const Thread& thread) = delete;
        virtual ~Thread() = default;

        void spawn(const ThreadData &threadData);

        void setAffinity(u64 affinity);

        void join();

        inline const std::thread::id getID() const { return std::this_thread::get_id() ; }
        static void sleepFor(u32 ms);
    };
}


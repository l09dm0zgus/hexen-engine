//
// Created by cx9ps3 on 13.07.2023.
//

#ifndef HEXENEDITOR_THREAD_H
#define HEXENEDITOR_THREAD_H

#include "ThreadLocalStorage.h"
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
        using  CallbackType = void(*)(Thread*);

        struct ThreadData
        {
            u32 numberOfFibers{25};
            std::shared_ptr<boost::fibers::buffered_channel<TaskInfo>> highPriorityTasks;
            std::shared_ptr<boost::fibers::buffered_channel<TaskInfo>> normalPriorityTasks;
            std::shared_ptr<boost::fibers::buffered_channel<TaskInfo>> lowPriorityTasks;
        };

    private:

        std::thread::id id{0};

        std::condition_variable receivedId;
        std::mutex startupIdMutex;

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

        void fromCurrentThread();

        inline ThreadLocalStorage* getStorage() { return &storage; }
        inline CallbackType getCallback() const { return callback; }
        inline vptr getUserData() const { return userData; }
        inline const std::thread::id getID() const { return std::this_thread::get_id() ; }
        void waitForReady();
        static void sleepFor(u32 ms);
    };
}

#endif //HEXENEDITOR_THREAD_H

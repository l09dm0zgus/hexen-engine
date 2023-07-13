//
// Created by cx9ps3 on 13.07.2023.
//

#ifndef HEXENEDITOR_THREAD_H
#define HEXENEDITOR_THREAD_H

#include "ThreadLocalStorage.h"
#include <mutex>
#include <condition_variable>

namespace core::threading
{
    class Thread
    {
    public:
        using  CallbackType = void(*)(Thread*);
    private:
        vptr handle{nullptr};
        u32 id = UINT32_MAX;
        ThreadLocalStorage storage;

        std::condition_variable receivedId;
        std::mutex startupIdMutex;

        CallbackType callback{nullptr};
        vptr userData{nullptr};

        Thread(vptr handle,u32 id) : handle(handle), id(id){}

    public:
        Thread() = default;
        Thread(const Thread& thread) = delete;
        virtual ~Thread() = default;

        bool spawn(CallbackType newCallback , vptr newUserdata = nullptr);

        void setAffinity(u64 affinity);

        void join();

        void fromCurrentThread();

        inline ThreadLocalStorage* getStorage() { return &storage; }
        inline CallbackType getCallback() const { return callback; }
        inline vptr getUserData() const { return userData; }
        inline bool hasSpawned() const { return id != UINT32_MAX; }
        inline const u32 getID() const { return id; }

        // Thread may launch before an ID was assigned (especially in Win32)
        // MSDN: If the thread is created in a runnable state (that is, if the
        //		 CREATE_SUSPENDED flag is not used), the thread can start running
        //		 before CreateThread returns and, in particular, before the caller
        //		 receives the handle and identifier of the created thread.
        // This scenario can cause a crash when the resulting callback wants to
        // access TLS.
        void waitForReady();

        static void sleepFor(u32 ms);
    };
}

#endif //HEXENEDITOR_THREAD_H

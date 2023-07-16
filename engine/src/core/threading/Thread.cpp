//
// Created by cx9ps3 on 13.07.2023.
//

#include "Thread.h"
#include <thread>
#include <chrono>

#if defined(WINDOWS_API)
#include <Windows.h>
#elif defined(POSIX_API)

#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#endif

static void  launchThread(core::vptr data)
{
    auto thread = reinterpret_cast<core::threading::Thread*>(data);

    assert(thread != nullptr && "thread object is nullptr");

    auto callback = thread->getCallback();

    assert(callback != nullptr && "thread callback is nullptr");

    thread->waitForReady();

    callback(thread);

}

void core::threading::Thread::spawn(core::threading::Thread::CallbackType newCallback, core::vptr newUserdata)
{
    id = std::thread::id(0);
    callback = newCallback;
    userData = newUserdata;
    receivedId.notify_all();

    std::lock_guard<std::mutex> lock(startupIdMutex);
    cppThread = std::thread(launchThread, this);

}

void core::threading::Thread::setAffinity(core::u64 affinity)
{
    auto handle = cppThread.native_handle();

#if defined(WINDOWS_API)

    DWORD_PTR mask = 1ull << affinity;
    SetThreadAffinityMask(handle, mask);

#elif defined(POSIX_API)

    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(affinity,&cpuset);


    if(handle == 0)
    {
        handle = pthread_self();
    }

    auto result = pthread_setaffinity_np(handle,sizeof(cpu_set_t),&cpuset);

    assert(result == 0 && "failed set affinity");

#endif

}

void core::threading::Thread::join()
{
    cppThread.detach();
}

void core::threading::Thread::fromCurrentThread()
{
    id = std::this_thread::get_id();
}

void core::threading::Thread::sleepFor(core::u32 ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void core::threading::Thread::waitForReady()
{
// Check if we have an ID already
    {
        std::lock_guard<std::mutex> lock(startupIdMutex);
        if (id != std::thread::id(0))
        {
            return;
        }
    }

    // Wait
    std::mutex mutex;

    std::unique_lock<std::mutex> lock(mutex);
    receivedId.wait(lock);
}



//
// Created by cx9ps3 on 13.07.2023.
//

#include "Thread.h"
#include <thread>
#include <sstream>
#if defined(WINDOWS_API)
#include <Windows.h>
#define ATTRIBUTE WINAPI
#elif defined(POSIX_API)

#define _GNU_SOURCE

#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#define ATTRIBUTE

#endif

static void* ATTRIBUTE launchThread(core::vptr data)
{
    auto thread = reinterpret_cast<core::threading::Thread*>(data);

    assert(thread != nullptr && "thread object is nullptr");

    auto callback = thread->getCallback();

    assert(callback != nullptr && "thread callback is nullptr");

    thread->waitForReady();
    callback(thread);

#if defined(POSIX_API)
    pthread_exit(nullptr);
#endif
}

bool core::threading::Thread::spawn(core::threading::Thread::CallbackType newCallback, core::vptr newUserdata)
{
    handle = nullptr;
    id = UINT64_MAX;
    callback = newCallback;
    userData = newUserdata;
    receivedId.notify_all();

#if defined(WINDOWS_API)

    std::lock_guard<std::mutex> lock(startupIdMutex);
    handle = CreateThread(0,0,(LPTHREAD_START_ROUTINE)launchThread, this, 0, (DWORD*)&id);

#elif defined(POSIX_API)

    std::lock_guard<std::mutex> lock(startupIdMutex);
    auto result = pthread_create(&id, nullptr, launchThread, this);
    assert(result == 0 && "failed to create thread");
    handle = reinterpret_cast<vptr>(id);
    std::cout << "Created thread  with id :" << id  << "\n";

#endif

    return hasSpawned();
}

void core::threading::Thread::setAffinity(core::u64 affinity)
{
    if (hasSpawned())
    {
        return;
    }
#if defined(WINDOWS_API)

    DWORD_PTR mask = 1ull << affinity;
    SetThreadAffinityMask(handle, mask);

#elif defined(POSIX_API)

    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(affinity,&cpuset);

    auto result = pthread_setaffinity_np(id,sizeof(cpuset),&cpuset);

    assert(result == 0 && "failed set affinity");

#endif

}

void core::threading::Thread::join()
{

    if (hasSpawned())
    {
        return;
    }

#if defined(WINDOWS_API)

    WaitForSingleObject(handle,INFINITE);

#elif defined(POSIX_API)

    auto result = pthread_join(id, nullptr);
    assert(result == 0 && "failed to join thread");
#endif
}

void core::threading::Thread::fromCurrentThread()
{

#if defined(WINDOWS_API)

    handle = GetCurrentThread();
    id = GetCurrentThreadId();


#elif defined(POSIX_API)

    if(id == UINT64_MAX)
    {
        id = pthread_self();
    }

    std::cout << "Current thread: " << id << "\n";

#endif



}

void core::threading::Thread::waitForReady()
{
    // Check if we have an ID already
    {
        std::lock_guard<std::mutex> lock(startupIdMutex);
        if (id != UINT64_MAX)
        {
            return;
        }
    }

    // Wait
    std::mutex mutex;

    std::unique_lock<std::mutex> lock(mutex);
    receivedId.wait(lock);
}

void core::threading::Thread::sleepFor(core::u32 ms)
{
#if defined(WINDOWS_API)

    Sleep(ms);

#elif defined(POSIX_API)

    usleep(ms);

#endif
}



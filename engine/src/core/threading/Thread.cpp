//
// Created by cx9ps3 on 13.07.2023.
//

#include "Thread.h"
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

static void ATTRIBUTE launchThread(core::vptr data)
{
    auto thread = reinterpret_cast<core::threading::Thread*>(data);

    assert(thread != nullptr && "thread object is nullptr");

    auto callback = thread->getCallback();

    assert(callback != nullptr && "thread callback is nullptr");

    thread->waitForReady();
    callback(thread);

}

bool core::threading::Thread::spawn(core::threading::Thread::CallbackType newCallback, core::vptr newUserdata)
{
    handle = nullptr;
    id = UINT32_MAX;
    callback = newCallback;
    userData = newUserdata;
    receivedId.notify_all();

#if defined(WINDOWS_API)

    std::lock_guard<std::mutex> lock(startupIdMutex);
    handle = CreateThread(0,0,(LPTHREAD_START_ROUTINE)launchThread, this, 0, (DWORD*)&id);

#elif defined(POSIX_API)

    pthread_t pthread;
    pthread_create(&pthread, nullptr, reinterpret_cast<void *(*)(void *)>(launchThread), this);
    id = pthread;
    handle = reinterpret_cast<vptr>(pthread);

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

    pthread_join(id, nullptr);

#endif
}

void core::threading::Thread::fromCurrentThread()
{

#if defined(WINDOWS_API)

    handle = GetCurrentThread();
    id = GetCurrentThreadId();

#elif defined(POSIX_API)

    id = pthread_self();
    handle = (vptr)pthread_self();

#endif

}

void core::threading::Thread::waitForReady()
{
    // Check if we have an ID already
    {
        std::lock_guard<std::mutex> lock(startupIdMutex);
        if (id != UINT32_MAX)
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



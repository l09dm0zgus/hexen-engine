
#include "Thread.hpp"

#if defined(HEXEN_WIN32_THREADS)

#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#	ifndef NOMINMAX
#		define NOMINMAX
#	endif
#	include <windows.h>

#	include <process.h>
#	include <cstdlib>

#	pragma warning(push)
#	pragma warning(disable : 4996) // 'mbstowcs': _CRT_SECURE_NO_WARNINGS

namespace hexen::engine::core::threading::thread
{

    static void setThreadName(HANDLE handle, const char *threadName)
    {
        const int bufferLenght = 128;
        WCHAR bufWide[bufferLenght];

        mbstowcs(bufWide, threadName, bufferLenght);
        bufWide[bufferLenght - 1] = '\0';

        // We can't call directly call "SetThreadDescription()" (
        // https://msdn.microsoft.com/en-us/library/windows/desktop/mt774976(v=vs.85).aspx ) here, as that would result in a vague DLL load
        // failure at launch, on any PC running Windows older than 10.0.14393. Luckily, we can work around this crash, and provide all the
        // benefits of "SetThreadDescription()", by manually poking into the local "kernel32.dll".
        HMODULE hMod = ::GetModuleHandleW(L"kernel32.dll");
        if (hMod)
        {
            using SetThreadDescriptionPtr_t = HRESULT(WINAPI *)(_In_ HANDLE hThread, _In_ PCWSTR lpThreadDescription);

            auto funcPtr = reinterpret_cast<SetThreadDescriptionPtr_t>(::GetProcAddress(hMod, "SetThreadDescription"));
            if (funcPtr != nullptr)
            {
                funcPtr(handle, bufWide);
            }
            else
            {
                // Failed to assign threads name. This requires Windows 10 Creators Update 2017, or newer, to have
                // threads names associated with debugging, profiling, and crash dumps
            }
        }
    }
#	pragma warning(pop)

    bool createThread(size_t stackSize, ThreadStartRoutine startRoutine, void *arg, const char *name, ThreadType *returnThread)
    {
        returnThread->Handle = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, (unsigned)stackSize, startRoutine, arg, 0u, nullptr));
        setThreadName(returnThread->Handle, name);
        returnThread->Id = ::GetThreadId(returnThread->Handle);

        return returnThread != nullptr;
    }

    bool createThread(size_t stackSize, ThreadStartRoutine startRoutine, void *arg, const char *name, size_t coreAffinity, ThreadType *returnThread)
    {
        returnThread->Handle = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, (unsigned)stackSize, startRoutine, arg, CREATE_SUSPENDED, nullptr));
        setThreadName(returnThread->Handle, name);
        returnThread->Id = ::GetThreadId(returnThread->Handle);

        if (returnThread->Handle == nullptr)
        {
            return false;
        }

        DWORD_PTR mask = 1ull << coreAffinity;
        ::SetThreadAffinityMask(returnThread, mask);
        ::ResumeThread(returnThread);

        return true;
    }

    void endCurrentThread()
    {
        _endthreadex(0);
    }

    bool joinThread(ThreadType threads)
    {
        auto result= ::WaitForSingleObject(threads.Handle, INFINITE);
        if (result == WAIT_OBJECT_0)
        {
            return true;
        }

        if (result == WAIT_ABANDONED)
        {
            return false;
        }

        return false;
    }

    ThreadType getCurrentThread()
    {
        return {::GetCurrentThread(), ::GetCurrentThreadId()};
    }

    bool setCurrentThreadAffinity(size_t coreAffinity)
    {
        auto result = ::SetThreadAffinityMask(::GetCurrentThread(), 1ULL << coreAffinity);
        return result != 0;
    }

    void sleepThread(int msDuration)
    {
        ::Sleep(msDuration);
    }

    void yieldThread()
    {
        ::SwitchToThread();
    }

}

#elif defined(HEXEN_POSIX_THREADS)

#	if defined(HEXEN_OS_LINUX)
#		include <features.h>
#	endif
#	include <pthread.h>
#	include <string.h>
#	include <unistd.h>

namespace hexen::engine::core::threading::thread
{
    bool createThread(size_t stackSize, ThreadStartRoutine startRoutine, void *arg, const char *name, ThreadType *returnThread)
    {
        (void)name;

        pthread_attr_t threadAttr;
        pthread_attr_init(&threadAttr);

        // Set stack size
        pthread_attr_setstacksize(&threadAttr, stackSize);

        int success = pthread_create(returnThread, &threadAttr, startRoutine, arg);

        // Cleanup
        pthread_attr_destroy(&threadAttr);

        return success == 0;
    }

    bool createThread(size_t stackSize, ThreadStartRoutine startRoutine, void *arg, const char *name, size_t coreAffinity, ThreadType *returnThread)
    {
        (void)name;

        pthread_attr_t threadAttr;
        pthread_attr_init(&threadAttr);

        // Set stack size
        pthread_attr_setstacksize(&threadAttr, stackSize);

        // TODO: OSX, MinGW, and musl Thread Affinity
        //       musl can set the affinity after the threads has been started (using pthread_setaffinity_np() )
        //       To set the affinity at threads creation, glibc created the pthread_attr_setaffinity_np() extension
#	if defined(HEXEN_OS_LINUX) && defined(__GLIBC__)
        // Set core affinity
        cpu_set_t cpuSet;
        CPU_ZERO(&cpuSet);
        CPU_SET(coreAffinity, &cpuSet);
        pthread_attr_setaffinity_np(&threadAttr, sizeof(cpu_set_t), &cpuSet);
#	else
        (void)coreAffinity;
#	endif

        auto success = pthread_create(returnThread, &threadAttr, startRoutine, arg);

        // Cleanup
        pthread_attr_destroy(&threadAttr);

        return success == 0;
    }

    void endCurrentThread()
    {
        pthread_exit(nullptr);
    }

    bool joinThread(ThreadType threads)
    {
        auto result = pthread_join(threads, nullptr);
        return  result == 0;
    }

    ThreadType getCurrentThread()
    {
        return pthread_self();
    }

    bool setCurrentThreadAffinity(size_t coreAffinity)
    {
        // TODO: OSX and MinGW Thread Affinity
#	if defined(HEXEN_OS_LINUX)
        cpu_set_t cpuSet;
        CPU_ZERO(&cpuSet);
        CPU_SET(coreAffinity, &cpuSet);

        auto result = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuSet);
        if (result != 0)
        {
            return false;
        }
#	else
        (void)coreAffinity;
#	endif

        return true;
    }

    void sleepThread(int msDuration)
    {
        usleep(static_cast<unsigned>(msDuration) * 1000);
    }

    void yieldThread()
    {
#	if defined(HEXEN_OS_LINUX)
        sched_yield();
#	endif
    }
}

#else
#	error No Thread library found
#endif

#include <thread>

namespace hexen::engine::core::threading::thread
{

    hexen::engine::core::u32 getNumberOfHardwareThreads()
    {
	    return std::thread::hardware_concurrency();
    }

}

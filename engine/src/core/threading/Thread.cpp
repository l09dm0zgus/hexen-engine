//
// Created by cx9ps3 on 13.07.2023.
//

#include "Thread.h"

#if defined(HEXEN_WIN32_THREADS)

    #	ifndef WIN32_LEAN_AND_MEAN

        #	define WIN32_LEAN_AND_MEAN

    #	endif

    #	ifndef NOMINMAX

        #	define NOMINMAX

    #	endif

    #	include <windows.h>

    #	include <process.h>
    #	include <stdlib.h>

    #	pragma warning(push)
    #	pragma warning(disable : 4996) // 'mbstowcs': _CRT_SECURE_NO_WARNINGS

    namespace core::threading
    {
        static void setThreadName(HANDLE handle, const char *threadName)
        {
	        const int bufLen = 128;
	        WCHAR bufWide[bufLen];

	        mbstowcs(bufWide, threadName, bufLen);
	        bufWide[bufLen - 1] = '\0';

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
			        // Failed to assign thread name. This requires Windows 10 Creators Update 2017, or newer, to have
			        // thread names associated with debugging, profiling, and crash dumps
                }
	        }
        }
    }

#	pragma warning(pop)
#elif defined(HEXEN_POSIX_THREADS)

    #	if defined(HEXEN_OS_LINUX)
        #		include <features.h>
    #	endif
    #	include <pthread.h>
    #	include <string.h>
    #	include <unistd.h>

#endif

bool core::threading::Thread::create(core::size stackSize, ThreadStartRoutine startRoutine, core::vptr arg,const std::string &name)
{
    #if defined(HEXEN_WIN32_THREADS)

        handle = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, (unsigned)stackSize, startRoutine, arg, 0u, nullptr));
        setThreadName(handle,name.c_str());
        id  = ::GetThreadId(handle);
        return handle != nullptr;

    #elif defined(HEXEN_POSIX_THREADS)

        (void)name;

        pthread_attr_t threadAttribute;
        pthread_attr_init(&threadAttribute);

        // Set stack size
        pthread_attr_setstacksize(&threadAttribute, stackSize);

        auto success = pthread_create(&handle, &threadAttribute, startRoutine, arg);

        // Cleanup
        pthread_attr_destroy(&threadAttribute);
        return success == 0;

    #endif

    return false;
}

bool core::threading::Thread::create(core::size stackSize, ThreadStartRoutine startRoutine, core::vptr arg,const std::string &name, core::size coreAffinity)
{
    #if defined(HEXEN_WIN32_THREADS)

        handle = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, (unsigned)stackSize, startRoutine, arg, CREATE_SUSPENDED, nullptr));
        setThreadName(handle,name.c_str());
        id  = ::GetThreadId(handle);

        if (handle == nullptr)
        {
		    return false;
        }

        setAffinity(coreAffinity);

        ::ResumeThread(handle);

        return true;

    #elif defined(HEXEN_POSIX_THREADS)

        (void)name;

        pthread_attr_t threadAttribute;
        pthread_attr_init(&threadAttribute);

        // Set stack size
        pthread_attr_setstacksize(&threadAttribute, stackSize);

        #if defined(HEXEN_OS_LINUX) && defined(__GLIBC__)

            // Set core affinity
            cpu_set_t cpuSet;
            CPU_ZERO(&cpuSet);
            CPU_SET(coreAffinity, &cpuSet);
            pthread_attr_setaffinity_np(&threadAttribute, sizeof(cpu_set_t), &cpuSet);

        #	else

            (void)coreAffinity;

        #	endif

            auto success = pthread_create(&handle, &threadAttribute, startRoutine, arg);

            // Cleanup
            pthread_attr_destroy(&threadAttribute);

            return success == 0;
    #endif

    return false;
}

void core::threading::Thread::close()
{
    Thread::endCurrentThread();
}

bool core::threading::Thread::join()
{
    #if defined(HEXEN_WIN32_THREADS)

        auto result = ::WaitForSingleObject(handle, INFINITE);

	    if (result == WAIT_OBJECT_0)
        {
		    return true;
	    }

	    if (result == WAIT_ABANDONED)
        {
		    return false;
	    }

    #elif defined(HEXEN_POSIX_THREADS)

        auto result = pthread_join(handle, nullptr);
        return result == 0;

    #endif

    return false;
}

void core::threading::Thread::yield()
{

    #if defined(HEXEN_WIN32_THREADS)

        ::SwitchToThread();

    #elif defined(HEXEN_POSIX_THREADS)

        pthread_yield();

    #endif

}

core::threading::ThreadType core::threading::Thread::getCurrentThread()
{

    #if defined(HEXEN_WIN32_THREADS)

        return {::GetCurrentThread(), ::GetCurrentThreadId()};

    #elif defined(HEXEN_POSIX_THREADS)

        return {pthread_self(), pthread_self()};

    #endif
}

void core::threading::Thread::sleep(core::u32 ms)
{
    #if defined(HEXEN_WIN32_THREADS)

    ::Sleep(ms);

    #elif defined(HEXEN_POSIX_THREADS)

    usleep(static_cast<unsigned>(ms) * 1000);

    #endif
}

#include <thread>

core::u32 core::threading::Thread::getNumberOfHardwareThread()
{
    return std::thread::hardware_concurrency();
}


bool core::threading::Thread::setAffinity(size coreAffinity)
{
    #if defined(HEXEN_WIN32_THREADS)

        DWORD_PTR mask = 1ull << coreAffinity;
        auto result = SetThreadAffinityMask(handle, mask);
        return result != 0;

    #elif defined(HEXEN_POSIX_THREADS)

        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(coreAffinity,&cpuset);


        if(handle == 0)
        {
            handle = pthread_self();
        }

        auto result = pthread_setaffinity_np(handle,sizeof(cpu_set_t),&cpuset);
        if (result != 0)
        {
		    return false;
        }

        return true;

    #endif
    return false;
}

void core::threading::Thread::endCurrentThread()
{
#if defined(HEXEN_WIN32_THREADS)

    _endthreadex(0);

#elif defined(HEXEN_POSIX_THREADS)

    pthread_exit(nullptr);

#endif
}

void core::threading::Thread::yieldCurrentThread()
{
#if defined(HEXEN_WIN32_THREADS)

    ::SwitchToThread();

#elif defined(HEXEN_POSIX_THREADS)

    pthread_yield();

#endif
}




#pragma once

#include "Config.hpp"


// Forward declare the platform types so we don't have to include their heavy header files
#if defined(HEXEN_WIN32_THREADS)

typedef void *HANDLE;
typedef unsigned long DWORD;

#elif defined(HEXEN_POSIX_THREADS)

#	if defined(HEXEN_OS_LINUX)
typedef unsigned long int pthread_t; // NOLINT(modernize-use-using)
#	elif defined(HEXEN_OS_APPLE)
struct _opaque_pthread_t;
typedef struct _opaque_pthread_t *__darwin_pthread_t; // NOLINT(modernize-use-using)
typedef __darwin_pthread_t pthread_t;                 // NOLINT(modernize-use-using)
#	endif
#endif

namespace hexen::engine::core::threading::thread
{
    // Create wrapper types so all our function signatures are the same
#if defined(HEXEN_WIN32_THREADS)

    struct Win32Thread {
        HANDLE Handle;
        DWORD Id;
    };

    typedef Win32Thread ThreadType; // NOLINT(modernize-use-using)

    typedef core::u32(__stdcall *ThreadStartRoutine)(void *arg); // NOLINT(modernize-use-using)
#	define HEXEN_THREAD_FUNC_RETURN_TYPE unsigned int
#	define HEXEN_THREAD_FUNC_DECL HEXEN_THREAD_FUNC_RETURN_TYPE __stdcall
#	define HEXEN_THREAD_FUNC_END return 0

#elif defined(HEXEN_POSIX_THREADS)

    typedef pthread_t ThreadType; // NOLINT(modernize-use-using)

typedef void *(*ThreadStartRoutine)(void *arg); // NOLINT(modernize-use-using)
#	define HEXEN_THREAD_FUNC_RETURN_TYPE void *
#	define HEXEN_THREAD_FUNC_DECL HEXEN_THREAD_FUNC_RETURN_TYPE
#	define HEXEN_THREAD_FUNC_END return nullptr

#else
#	error No Thread library found
#endif

    bool createThread(size_t stackSize, ThreadStartRoutine startRoutine, void *arg, const char *name, ThreadType *returnThread);

    bool createThread(size_t stackSize, ThreadStartRoutine startRoutine, void *arg, const char *name, size_t coreAffinity, ThreadType *returnThread);


    ThreadType getCurrentThread();


    void endCurrentThread();


    bool joinThread(ThreadType thread);


    bool setCurrentThreadAffinity(size_t coreAffinity);


    void sleepThread(int msDuration);


    void yieldThread();


    core::u32 getNumberOfHardwareThreads();

}

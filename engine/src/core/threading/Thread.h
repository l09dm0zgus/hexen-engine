//
// Created by cx9ps3 on 13.07.2023.
//

#pragma once

#include "Config.h"
#if defined(HEXEN_WIN32_THREADS)

using HANDLE = core::vptr;
using DWORD = unsigned long;

using NativeHandle = HANDLE;
using Id = DWORD;




#elif defined(HEXEN_POSIX_THREADS)

    #	if defined(HEXEN_OS_LINUX)

        using pthread_t = unsigned long int;

        using NativeHandle = pthread_t;
        using Id = NativeHandle;

    #	elif defined(HEXEN_OS_APPLE)

        struct _opaque_pthread_t;
        typedef struct _opaque_pthread_t *__darwin_pthread_t; // NOLINT(modernize-use-using)
        using pthread_t = __darwin_pthread_t;

        using NativeHandle =  pthread_t;
        using Id = NativeHandle;

    #	endif


#endif

#if defined(HEXEN_WIN32_THREADS)

    typedef unsigned int(__stdcall *ThreadStartRoutine)(core::vptr arg); // NOLINT(modernize-use-using)
    #	define HEXEN_THREAD_FUNC_RETURN_TYPE unsigned int
    #	define HEXEN_THREAD_FUNC_DECL HEXEN_THREAD_FUNC_RETURN_TYPE __stdcall
    #	define HEXEN_THREAD_FUNC_END return 0

#elif defined(HEXEN_POSIX_THREADS)

    typedef pthread_t ThreadType; // NOLINT(modernize-use-using)

    typedef core::vptr (*ThreadStartRoutine)(core::vptr arg); // NOLINT(modernize-use-using)
    #	define HEXEN_THREAD_FUNC_RETURN_TYPE core::vptr
    #	define HEXEN_THREAD_FUNC_DECL HEXEN_THREAD_FUNC_RETURN_TYPE
    #	define HEXEN_THREAD_FUNC_END return nullptr

#else
#	error No Thread library found
#endif

namespace core::threading
{

    struct ThreadType
    {
        NativeHandle  handle;
        Id id;
    };

    class Thread
    {
    private:

        NativeHandle handle;
        Id id;


    public:
        Thread() = default;

        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;

        bool create(size stackSize,ThreadStartRoutine startRoutine,vptr arg,const std::string &name);

        bool create(size stackSize,ThreadStartRoutine startRoutine,vptr arg,const std::string &name , size coreAffinity);

        void close();

        bool join();

        bool setAffinity(size coreAffinity);

        void yield();



        inline NativeHandle getNativeHandle() const noexcept { return handle; }
        inline Id getId() const noexcept { return id; }

        static ThreadType getCurrentThread();

        static void sleep(u32 ms);

        static u32 getNumberOfHardwareThread();

    };
}


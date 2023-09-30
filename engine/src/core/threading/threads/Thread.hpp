
#pragma once

#include "Config.hpp"


// Forward declare the platform types so we don't have to include their heavy header files
#if defined(HEXEN_WIN32_THREADS)

typedef void *HANDLE;
typedef unsigned long DWORD;

#elif defined(HEXEN_POSIX_THREADS)

	#if defined(HEXEN_OS_LINUX)
        #if defined(__ANDROID__)
            typedef hexen::engine::core::i64 pthread_t;
        #else
            typedef hexen::engine::core::u64 pthread_t;
        #endif
	#elif defined(HEXEN_OS_APPLE)
        struct _opaque_pthread_t;
        typedef struct _opaque_pthread_t *__darwin_pthread_t;
	#endif
#endif

namespace hexen::engine::core::threading::thread
{
	// Create wrapper types so all our function signatures are the same
#if defined(HEXEN_WIN32_THREADS)

	/**
 	* @brief Represents a thread in Win32.
 	*/

	struct Win32Thread
	{
		HANDLE Handle;
		DWORD Id;
	};

	using ThreadType = Win32Thread ;// NOLINT(modernize-use-using)

	typedef core::u32(__stdcall *ThreadStartRoutine)(hexen::engine::core::vptr arg);///@brief Function pointer typedef for the thread start routine.
	#define HEXEN_THREAD_FUNC_RETURN_TYPE hexen::engine::core::u32
	#define HEXEN_THREAD_FUNC_DECL HEXEN_THREAD_FUNC_RETURN_TYPE __stdcall
	#define HEXEN_THREAD_FUNC_END return 0

#elif defined(HEXEN_POSIX_THREADS)

	using ThreadType = pthread_t;

	typedef void *(*ThreadStartRoutine)(hexen::engine::core::vptr arg); ///@brief Function pointer typedef for the thread start routine.
	#define HEXEN_THREAD_FUNC_RETURN_TYPE hexen::engine::core::vptr
	#define HEXEN_THREAD_FUNC_DECL HEXEN_THREAD_FUNC_RETURN_TYPE
	#define HEXEN_THREAD_FUNC_END return nullptr

#else
	#error No Thread library found
#endif

	/**
 	* @brief Creates a new thread
 	* @param stackSize The stack size for the new thread.
 	* @param startRoutine The start routine for the new thread.
 	* @param arg Argument to pass to the start routine.
 	* @param name The name of the new thread.
 	* @param returnThread A point to a ThreadType to return the created thread.
 	* @return true if successful, false otherwise.
 	*/

	bool createThread(size_t stackSize, ThreadStartRoutine startRoutine, void *arg, const char *name, ThreadType *returnThread);

	/**
 	* @brief Creates a new thread with specific core affinity.
 	* @param stackSize The stack size for the new thread.
 	* @param startRoutine The start routine for the new thread.
 	* @param arg Argument to pass to the start routine.
 	* @param name The name of the new thread.
 	* @param coreAffinity The core affinity for the new thread.
 	* @param returnThread A point to a ThreadType to return the created thread.
 	* @return true if successful, false otherwise.
 	*/

	bool createThread(size_t stackSize, ThreadStartRoutine startRoutine, void *arg, const char *name, size_t coreAffinity, ThreadType *returnThread);

	/**
 	* @brief Retrieves the current thread.
 	* @return The current thread.
 	*/

	ThreadType getCurrentThread();

	/**
 	* @brief Ends the current thread.
 	*/

	void endCurrentThread();

	/**
 	* @brief Joins a specific thread.
 	* @param thread The thread to join.
 	* @return true if successful, false otherwise.
 	*/

	bool joinThread(ThreadType thread);

	/**
 	* @brief Sets the affinity of the current thread to a specific core.
 	* @param coreAffinity The core to set the current thread affinity to.
 	* @return true if successful, false otherwise.
 	*/

	bool setCurrentThreadAffinity(size_t coreAffinity);

	/**
 	* @brief Puts the current thread to sleep for a specific duration.
 	* @param msDuration The duration in milliseconds for the thread to sleep.
 	*/

	void sleepThread(int msDuration);

	/**
 	* @brief Yields the current thread.
 	*/

	void yieldThread();

	/**
 	* @brief Retrieves the number of hardware threads.
 	* @return The number of hardware threads.
 	*/

	core::u32 getNumberOfHardwareThreads();

}// namespace hexen::engine::core::threading::thread

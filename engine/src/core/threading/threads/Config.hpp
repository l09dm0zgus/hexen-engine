
#pragma once
#include "../../Types.hpp"

#ifndef HEXEN_DEBUG
	#ifndef NDEBUG
		#define HEXEN_DEBUG 1
	#else
		#define FTL_DEBUG 0
	#endif
#endif


#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
	#define HEXEN_WIN32_THREADS
#elif defined(HEXEN_OS_MAC) || defined(HEXEN_OS_iOS) || defined(HEXEN_OS_LINUX)
	#include <unistd.h>

	#if defined(_POSIX_VERSION)
		#define HEXEN_POSIX_THREADS
	#endif
#endif

//               SSE on MSVC x86                            MSVC x64 has SSE              Clang/GCC define
#if (defined(_M_IX86_FP) && _M_IX86_FP >= 1) || (defined(_M_AMD64) || defined(_M_X64)) || defined(__SSE__)
	#include <emmintrin.h>
	#define HEXEN_PAUSE() _mm_pause();
#elif defined __aarch64__
	#define HEXEN_PAUSE() asm volatile("isb" \
									   :     \
									   :);
#else
	#define HEXEN_PAUSE() std::this_thread::yield();
#endif


#if defined(HEXEN_POSIX_THREADS)
	#define HEXEN_NOINLINE_POSIX __attribute__((noinline))
	#define HEXEN_NOINLINE_WIN32
	#define HEXEN_NOINLINE HEXEN_NOINLINE_POSIX
#elif defined(HEXEN_WIN32_THREADS)
	#define HEXEN_NOINLINE_POSIX
	#define HEXEN_NOINLINE_WIN32 __declspec(noinline)
	#define HEXEN_NOINLINE HEXEN_NOINLINE_WIN32
#else
	#define HEXEN_NOINLINE_POSIX
	#define HEXEN_NOINLINE_WIN32
	#define HEXEN_NOINLINE
#endif

#ifdef __cpp_lib_hardware_interference_size
	#include <new>
#endif

namespace hexen::engine::core::threading
{
#ifdef __cpp_lib_hardware_interference_size
	constexpr static size_t cacheLineSize = std::hardware_destructive_interference_size;
#else
	constexpr static size_t cacheLineSize = 64;
#endif
}// namespace hexen::engine::core::threading

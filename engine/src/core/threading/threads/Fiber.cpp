
#include "Fiber.hpp"
#include "Config.hpp"

#include <algorithm>

#if defined(HEXEN_FIBER_STACK_GUARD_PAGES)
	#if defined(HEXEN_OS_LINUX) || defined(HEXEN_OS_MAC) || defined(HEXEN_OS_iOS)
		#include <sys/mman.h>
		#include <unistd.h>
	#elif defined(HEXEN_OS_WINDOWS)
		#define WIN32_LEAN_AND_MEAN
		#define NOMINMAX
		#include <Windows.h>
	#endif
#endif

namespace hexen::engine::core::threading
{
	void memoryGuard(vptr memory, size_t bytes);
	void memoryGuardRelease(vptr memory, size_t bytes);
	size_t systemPageSize();
	void *alignedAlloc(size_t size, size_t alignment);
	void alignedFree(void *block);
	size_t roundUp(size_t numberToRound, size_t multiple);

	Fiber::Fiber(size_t stackSize, fiberStartRoutine startRoutine, void *arg) : arg(arg)
	{
#if defined(HEXEN_FIBER_STACK_GUARD_PAGES)
		systemPageSize = SystemPageSize();
#else
		systemPageSize = 0;
#endif

		this->stackSize = roundUp(stackSize, systemPageSize);
		// We add a guard page both the top and the bottom of the stack
		stack = alignedAlloc(systemPageSize + this->stackSize + systemPageSize, systemPageSize);
		context = boost_context::make_fcontext(static_cast<char *>(stack) + systemPageSize + stackSize, stackSize, startRoutine);

#if defined(HEXEN_FIBER_STACK_GUARD_PAGES)
		memoryGuard(static_cast<char *>(stack), systemPageSize);
		memoryGuard(static_cast<char *>(stack) + systemPageSize + stackSize, systemPageSize);
#endif
	}

	Fiber::~Fiber()
	{
		if (stack != nullptr)
		{
			if (systemPageSize != 0)
			{
				memoryGuardRelease(static_cast<char *>(stack), systemPageSize);
				memoryGuardRelease(static_cast<char *>(stack) + systemPageSize + stackSize, systemPageSize);
			}

			alignedFree(stack);
		}
	}

	void Fiber::swap(Fiber &first, Fiber &second) noexcept
	{
		std::swap(first.stack, second.stack);
		std::swap(first.systemPageSize, second.systemPageSize);
		std::swap(first.stackSize, second.stackSize);
		std::swap(first.context, second.context);
		std::swap(first.arg, second.arg);
	}

#if defined(HEXEN_FIBER_STACK_GUARD_PAGES)
	#if defined(HEXEN_OS_LINUX) || defined(HEXEN_OS_MAC) || defined(HEXEN_OS_iOS)
	void memoryGuard(vptr memory, size_t bytes)
	{
		auto result = mprotect(memory, bytes, PROT_NONE);
		HEXEN_ASSERT(!result, "mprotect");
		#if defined(NDEBUG)
		// Void out the result for release, so the compiler doesn't get cranky about an unused variable
		(void) result;
		#endif
	}

	void memoryGuardRelease(vptr memory, size_t bytes)
	{
		auto const result = mprotect(memory, bytes, PROT_READ | PROT_WRITE);
		HEXEN_ASSERT(!result, "mprotect");
		#if defined(NDEBUG)
		// Void out the result for release, so the compiler doesn't get cranky about an unused variable
		(void) result;
		#endif
	}

	size_t systemPageSize()
	{
		return static_cast<size_t>(getpagesize());
	}

	void *alignedAlloc(size_t size, size_t alignment)
	{
		vptr returnPtr = nullptr;
		auto const result = posix_memalign(&returnPtr, alignment, size);
		HEXEN_ASSERT(!result, "posix_memalign");
		#if defined(NDEBUG)
		// Void out the result for release, so the compiler doesn't get cranky about an unused variable
		(void) result;
		#endif

		return returnPtr;
	}

	void alignedFree(vptr block)
	{
		free(block);
	}
	#elif defined(HEXEN_OS_WINDOWS)


	void memoryGuard(vptr memory, size_t bytes)
	{
		DWORD ignored;

		auto const result = VirtualProtect(memory, bytes, PAGE_NOACCESS, &ignored);
		HEXEN_ASSERT(result, " VirtualProtect");
	}

	void memoryGuardRelease(vptr memory, size_t bytes)
	{
		DWORD ignored;

		auto const result = VirtualProtect(memory, bytes, PAGE_READWRITE, &ignored);
		FTL_ASSERT("VirtualProtect", result);
	}

	size_t systemPageSize()
	{
		SYSTEM_INFO sysInfo;
		GetSystemInfo(&sysInfo);
		return sysInfo.dwPageSize;
	}

	void *alignedAlloc(size_t size, size_t alignment)
	{
		return _aligned_malloc(size, alignment);
	}

	void alignedFree(vptr block)
	{
		_aligned_free(block);
	}
	#else
		#error "Need a way to protect memory for this platform".
	#endif
#else

	void memoryGuard(vptr memory, size_t bytes)
	{
		(void) memory;
		(void) bytes;
	}

	void memoryGuardRelease(vptr memory, size_t bytes)
	{
		(void) memory;
		(void) bytes;
	}

	size_t systemPageSize()
	{
		return 0;
	}

	void *alignedAlloc(size_t size, size_t /*alignment*/)
	{
		return malloc(size);
	}

	void alignedFree(vptr block)
	{
		free(block);
	}
#endif

	size_t roundUp(size_t numberToRound, size_t multiple)
	{
		if (multiple == 0)
		{
			return numberToRound;
		}

		size_t const remainder = numberToRound % multiple;
		if (remainder == 0)
		{
			return numberToRound;
		}

		return numberToRound + multiple - remainder;
	}

}// namespace hexen::engine::core::threading
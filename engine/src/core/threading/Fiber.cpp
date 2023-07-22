//
// Created by cx9ps3 on 18.07.2023.
//

#include "Fiber.h"
#include "../Types.h"
#include "Config.h"

#if defined(HEXEN_FIBER_STACK_GUARD_PAGES)
#	if defined(HEXEN_OS_LINUX) || defined(HEXEN_OS_MAC) || defined(HEXEN_OS_iOS)
#		include <sys/mman.h>
#		include <unistd.h>
#	elif defined(HEXEN_OS_WINDOWS)
#		define WIN32_LEAN_AND_MEAN
#		define NOMINMAX
#		include <Windows.h>
#	endif
#endif

namespace core::threading::mem
    {
        void memoryGuard(vptr memory , size bytes);
        void memoryGuardRelease(vptr memory, size bytes);
        size getSystemPageSize();
        vptr alignedAllocation(size bytes,size alignment);
        void alignedFree(vptr block);
        size roundUp(size numberToRound,size multiple);
    }

core::threading::Fiber::Fiber(core::size stackSize, core::threading::FiberStartRoutine startRoutine, core::vptr arg):arg(arg)
{
#if defined(HEXEN_FIBER_STACK_GUARD_PAGES)

    systemPageSize = mem::getSystemPageSize();

#else

    systemPageSize = 0;

#endif

    this->stackSize = mem::roundUp(stackSize,systemPageSize);

    stack = mem::alignedAllocation(systemPageSize + this->stackSize + systemPageSize,systemPageSize);

    context = boost_context::make_fcontext(static_cast<char *>(stack) + systemPageSize + stackSize, stackSize,startRoutine);

#if defined(HEXEN_FIBER_STACK_GUARD_PAGES)

    mem::memoryGuard(static_cast<char *>(stack), systemPageSize);
	mem::memoryGuard(static_cast<char *>(stack) + systemPageSize + stackSize,systemPageSize);

#endif
}

core::threading::Fiber::~Fiber()
{
    if(stack != nullptr)
    {
        if(systemPageSize)
        {
            mem::memoryGuardRelease(static_cast<char *>(stack), systemPageSize);
            mem::memoryGuardRelease(static_cast<char *>(stack) + systemPageSize + stackSize, systemPageSize);
        }
        mem::alignedFree(stack);
    }
}

void core::threading::Fiber::swap(core::threading::Fiber &first, core::threading::Fiber &second) noexcept
{
    std::swap(first.stack, second.stack);
    std::swap(first.systemPageSize, second.systemPageSize);
    std::swap(first.stackSize, second.stackSize);
    std::swap(first.context, second.context);
    std::swap(first.arg, second.arg);
}
#if defined(HEXEN_FIBER_STACK_GUARD_PAGES)
HEXEN_INLINE void core::threading::mem::memoryGuard(core::vptr memory, core::size bytes)
{
#	if defined(HEXEN_OS_LINUX) || defined(HEXEN_OS_MAC) || defined(HEXEN_OS_iOS)

    auto result = mprotect(memory, bytes, PROT_NONE);
	HEXEN_ASSERT(!result,"mprotect:failed to protect memory");

    #if defined(NDEBUG)

	    // Void out the result for release, so the compiler doesn't get cranky about an unused variable
	    (void)result;

    #endif

#	elif defined(HEXEN_OS_WINDOWS)

        DWORD ignored;
        auto result = VirtualProtect(memory, bytes, PAGE_NOACCESS, &ignored);

        HEXEN_ASSERT(result,"VirtualProtect:failed to protect memory");

        #if defined(NDEBUG)

            // Void out the result for release, so the compiler doesn't get cranky about an unused variable
	        (void)result;

        #endif

#	endif
}

HEXEN_INLINE void core::threading::mem::memoryGuardRelease(vptr memory, size bytes)
{
    #	if defined(HEXEN_OS_LINUX) || defined(HEXEN_OS_MAC) || defined(HEXEN_OS_iOS)

    auto result = mprotect(memory, bytes, PROT_READ | PROT_WRITE);
	HEXEN_ASSERT(!result,"mprotect:failed to protect memory");

    #if defined(NDEBUG)

	    // Void out the result for release, so the compiler doesn't get cranky about an unused variable
	    (void)result;

    #endif

#	elif defined(HEXEN_OS_WINDOWS)

        DWORD ignored;
        auto result = VirtualProtect(memory, bytes, PAGE_READWRITE, &ignored);

        HEXEN_ASSERT(result,"VirtualProtect:failed to protect memory");

        #if defined(NDEBUG)

            // Void out the result for release, so the compiler doesn't get cranky about an unused variable
	        (void)result;

        #endif

#	endif
}

HEXEN_INLINE core::size core::threading::mem::getSystemPageSize()
{
#	if defined(HEXEN_OS_LINUX) || defined(HEXEN_OS_MAC) || defined(HEXEN_OS_iOS)

    return static_cast<size>(getpagesize());

#	elif defined(HEXEN_OS_WINDOWS)

    SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	return sysInfo.dwPageSize;

#endif

}

HEXEN_INLINE core::vptr core::threading::mem::alignedAllocation(size bytes,size alignment)
{
#	if defined(HEXEN_OS_LINUX) || defined(HEXEN_OS_MAC) || defined(HEXEN_OS_iOS)

    vptr returnPtr = nullptr;
	auto result = posix_memalign(&returnPtr, alignment, size);
	HEXEN_ASSERT(!result,"posix_memalign:failed to allocate memory");

    #	if defined(NDEBUG)

	    // Void out the result for release, so the compiler doesn't get cranky about an unused variable
	    (void)result;

    #	endif

	return returnPtr;

#	elif defined(FTL_OS_WINDOWS)

   return _aligned_malloc(size, alignment);

#endif
}

HEXEN_INLINE void core::threading::mem::alignedFree(vptr block)
{
#	if defined(HEXEN_OS_LINUX) || defined(HEXEN_OS_MAC) || defined(HEXEN_OS_iOS)

    free(block);

#	elif defined(FTL_OS_WINDOWS)

   _aligned_free(block);

#endif
}

#else

HEXEN_INLINE void core::threading::mem::memoryGuard(core::vptr memory, core::size bytes)
{
    (void)memory;
    (void)bytes;
}

HEXEN_INLINE void core::threading::mem::memoryGuardRelease(core::vptr memory, core::size bytes)
{
    (void)memory;
    (void)bytes;
}

HEXEN_INLINE core::size core::threading::mem::getSystemPageSize() { return 0;}

HEXEN_INLINE core::vptr core::threading::mem::alignedAllocation(core::size bytes, core::size alignment)
{
    return malloc(bytes);
}

HEXEN_INLINE void core::threading::mem::alignedFree(core::vptr block)
{
    free(block);
}

HEXEN_INLINE core::size core::threading::mem::roundUp(core::size numberToRound, core::size multiple)
{
    if (multiple == 0)
    {
        return numberToRound;
    }

    auto const remainder = numberToRound % multiple;

    if (remainder == 0)
    {
        return numberToRound;
    }

    return numberToRound + multiple - remainder;
}


#endif
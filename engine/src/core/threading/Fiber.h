//
// Created by cx9ps3 on 18.07.2023.
//

#pragma once

#include "../Types.h"
#include <fcontext/fcontext.h>

namespace core::threading
{
    using FiberStartRoutine = void (*)(vptr arg);
    class Fiber
    {
    public:
        Fiber() = default;

        Fiber(size stackSize,FiberStartRoutine startRoutine, vptr arg);

        Fiber(Fiber const &other) = delete;

        Fiber &operator=(Fiber const &other) = delete;

        Fiber(Fiber &&other) noexcept :  Fiber()
        {
            swap(*this,other);
        }

        Fiber& operator=(Fiber&& other) noexcept
        {
            if(this == &other)
            {
               return *this;
            }
            swap(*this,other);
            return *this;
        }

        HEXEN_INLINE void switchToFiber(Fiber* const fiber)
        {
            jump_fcontext(fiber->context,fiber->arg);
        }

        HEXEN_INLINE void reset(FiberStartRoutine const startRoutine , vptr const arg)
        {
            context = make_fcontext(static_cast<char *>(stack) + stackSize, stackSize, (pfn_fcontext) startRoutine);
        }

    ~Fiber();
    private:
        vptr stack{nullptr};
        size systemPageSize{0};
        size stackSize{0};
        fcontext_t context{nullptr};
        vptr arg{nullptr};

        static void swap(Fiber &first, Fiber &second) noexcept;
    };
}



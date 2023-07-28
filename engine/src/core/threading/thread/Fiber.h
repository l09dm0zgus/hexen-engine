
#pragma once

#include <boost_context/fcontext.h>

#include "../../Types.h"

namespace core::threading
{

    using FiberStartRoutine = void (*)(void *arg);

    class Fiber
    {
    public:

	    Fiber() = default;

	    Fiber(size_t stackSize, FiberStartRoutine startRoutine, void *arg);


	    Fiber(Fiber const &other) = delete;

	    Fiber &operator=(Fiber const &other) = delete;


	    Fiber(Fiber &&other) noexcept: Fiber()
        {
            swap(*this, other);
	    }

	    Fiber &operator=(Fiber &&other) noexcept
        {
            swap(*this, other);

		    return *this;
	    }
	    ~Fiber();

    private:
	    void *stack{nullptr};
	    size_t systemPageSize{0};
	    size_t stackSize{0};
	    boost_context::fcontext_t context{nullptr};
	    void *arg{nullptr};

public:

	void switchToFiber(Fiber *const fiber)
    {
		boost_context::jump_fcontext(&context, fiber->context, fiber->arg);
	}

	void reset(FiberStartRoutine const startRoutine, void *const arg)
    {
        context = boost_context::make_fcontext(static_cast<char *>(stack) + stackSize, stackSize, startRoutine);
        this->arg = arg;
	}

private:

	static void swap(Fiber &first, Fiber &second) noexcept;
};

}

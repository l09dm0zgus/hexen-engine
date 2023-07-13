//
// Created by cx9ps3 on 13.07.2023.
//

#include "Fiber.h"

#if defined(WINDOWS_API)
#include <Windows.h>
#elif defined(POSIX_API)

#include <stdlib.h>
#include <assert.h>
#include <ucontext.h>
#include <bits/sigstksz.h>

#endif
static void launchFiber(core::threading::Fiber* fiber)
{
    auto callback = fiber->getCallback();
    assert(callback != nullptr && "callback is nullptr");
    callback(fiber);

}

core::threading::Fiber::Fiber()
{
#if defined(WINDOWS_API)
    fiber = CreateFiber(0,(LPFIBER_START_ROUTINE) launchFiber, this);
    isThreadFiber = false;
#elif defined(POSIX_API)
    auto* context = new ucontext_t();
    getcontext(context);
    context->uc_link = nullptr;
    context->uc_stack.ss_sp = malloc(SIGSTKSZ);
    context->uc_stack.ss_size = SIGSTKSZ;
    context->uc_stack.ss_flags = 0;
    makecontext(context, reinterpret_cast<void (*)(void)>(launchFiber), 1, this);
    fiber = context;
#endif
}

core::threading::Fiber::~Fiber()
{
#if defined(WINDOWS_API)
    if (fiber && !isThreadFiber)
    {
		DeleteFiber(fiber);
	}
#elif defined(POSIX_API)

    if(isValid())
    {
        ucontext_t* context = (ucontext_t*)fiber;
        free(context->uc_stack.ss_sp);
        delete context;
        fiber = nullptr;
    }

#endif

}

void core::threading::Fiber::setCallback(core::threading::Fiber::CallbackType newCallback)
{
    assert(newCallback != nullptr && "callback i s nullptr");
    this->callback = newCallback;
}

void core::threading::Fiber::switchTo(core::threading::Fiber *fiber, core::vptr data)
{
    assert(fiber != nullptr && fiber->fiber != nullptr && "fiber is nullptr or invalid");

    fiber->userData = data;
    fiber->returnFiber = this;

#if defined(WINDOWS_API)

    SwitchToFiber(fiber->fiber);

#elif defined(POSIX_API)

    auto context = (ucontext_t*)fiber->fiber;
    setcontext(context);

#endif
}

void core::threading::Fiber::switchBack()
{
    assert(returnFiber != nullptr && returnFiber->fiber != nullptr && "return fiber is nullptr or invalid");

#if defined(WINDOWS_API)

    SwitchToFiber(returnFiber->fiber);

#elif defined(POSIX_API)

    auto context = (ucontext_t*)returnFiber->fiber;
    setcontext(context);

#endif

}

void core::threading::Fiber::convertFromCurrentThread()
{
#if defined(WINDOWS_API)

    SwitchToFiber(returnFiber->fiber);

    if (fiber && !isThreadFiber)
    {
        DeleteFiber(fiber);
    }

    fiber = ConvertThreadToFiber(nullptr);
    isThreadFiber = true;

#endif
}

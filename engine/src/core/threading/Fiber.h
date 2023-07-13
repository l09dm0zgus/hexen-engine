//
// Created by cx9ps3 on 13.07.2023.
//

#ifndef HEXENEDITOR_FIBER_H
#define HEXENEDITOR_FIBER_H
#include "../Types.h"

namespace core::threading
{
    class Fiber
    {
    public:
        using CallbackType = void(*)(Fiber*);
        Fiber();
        ~Fiber();
        Fiber(const Fiber&) = delete;
        void convertFromCurrentThread();
        void setCallback(CallbackType newCallback);
        void switchTo(Fiber* fiber,vptr data = nullptr);
        void switchBack();

        inline CallbackType getCallback() const { return callback; }
        inline vptr getUserData() const { return  userData; }
        inline bool isValid() const { return fiber && callback; }

    private:
        explicit Fiber(vptr fiber) :fiber(fiber){};

        vptr fiber{nullptr};
        bool isThreadFiber{false};
        Fiber* returnFiber{nullptr};
        CallbackType callback{nullptr};
        vptr userData{nullptr};
    };
}




#endif //HEXENEDITOR_FIBER_H

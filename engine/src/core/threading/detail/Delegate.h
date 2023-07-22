//
// Created by cx9ps3 on 14.07.2023.
//

#pragma once


#include "Details.h"
#include "FunctionChecks.h"


namespace core::threading::detail
{
    struct BaseDelegate
    {
        virtual ~BaseDelegate() = default;
        virtual void call() = 0;
    };

    // callable: function pointer or lambda class
    template <typename TCallable, typename... Args>
    struct DelegateCallable : BaseDelegate
    {
        TCallable callable;
        std::tuple<Args...> args;

        explicit DelegateCallable(TCallable callable, Args... args) :callable(callable),args(args...)
        {};

        ~DelegateCallable() override = default;

        void call() override
        {
            apply(callable, args);
        }
    };

    // member: member function
    template <class TClass, typename Ret, typename... Args>
    struct DelegateMember : BaseDelegate
    {
        using function_t = Ret(TClass::*)(Args...);
        function_t function;
        TClass* instance;
        std::tuple<Args...> args;

        DelegateMember(function_t function, TClass* inst, Args... args) : function(function),instance(inst),args(args...)
        {};

        ~DelegateMember() override = default;

        void call() override
        {
            apply(instance, function, args);
        }
    };
}


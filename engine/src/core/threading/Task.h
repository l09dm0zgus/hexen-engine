//
// Created by cx9ps3 on 14.07.2023.
//

#pragma once


#include "../Types.h"
#include "detail/Delegate.h"
#include "TaskCounter.h"
#include <string.h>
#include <memory>

namespace core::threading
{
    class TaskCounter;
    class TaskManager;
    class TaskInfo
    {
    private:
        friend class TaskManager;
        static constexpr u64 bufferSize = sizeof(vptr) * (8);
        char buffer[bufferSize]{0};
        inline detail::BaseDelegate* getDelegate() { return reinterpret_cast<detail::BaseDelegate*>(buffer) ;}
        inline bool isNull() const { return *(void**)buffer == nullptr; }

        void reset()
        {
            if(!isNull())
            {
                getDelegate()->~BaseDelegate();
                *(void**)buffer = nullptr;
            }
        }

        template <typename delegate_t, typename... Args>
        void storeJobInfo(Args... args)
        {
            detail::DelegateSizeChecker<sizeof(delegate_t), bufferSize>::check();
            new(buffer) delegate_t(args...);
        }

        template <class TClass, typename... Args>
        void storeJobInfo(TClass* inst, Args... args)
        {
            using Ret = typename detail::FunctionTraits<TClass>::ReturnType;
            storeJobInfo<typename detail::DelegateMember<TClass, Ret, Args...>>(&TClass::operator(), inst, args...);
        }

      TaskCounter *counter = nullptr;

    public:
        TaskInfo() = default;

        template <typename TCallable, typename... Args>
        TaskInfo( TaskCounter *counter , TCallable callable, Args... args) : counter(counter)
        {
            reset();
            detail::FunctionChecker<TCallable, Args...>::check();
            storeJobInfo<typename detail::DelegateCallable<TCallable, Args...>>(callable, args...);
        }

        template <typename Ret, typename... Args>
        TaskInfo(TaskCounter *counter, Ret(*function)(Args...), Args... args) :counter(counter)
        {
            reset();
            detail::FunctionChecker<decltype(function), Args...>::check();
            storeJobInfo<typename detail::DelegateCallable<decltype(function), Args...>>(function, args...);
        }

        template <class TCallable, typename... Args>
        TaskInfo(TaskCounter *counter, TCallable* callable, Args... args) : counter(counter)
        {
            reset();
            detail::FunctionChecker<TCallable, Args...>::check();
            storeJobInfo(callable, args...);
        }

        template <class TClass, typename Ret, typename... Args>
        TaskInfo(TaskCounter *counter, Ret(TClass::* callable)(Args...), TClass* inst, Args... args) : counter(counter)
        {
            reset();
            detail::FunctionChecker<decltype(callable), TClass*, Args...>::check();
            storeJobInfo<typename detail::DelegateMember<TClass, Ret, Args...>>(callable, inst, args...);
        }

        template <typename TCallable, typename... Args>
        explicit TaskInfo(TCallable callable, Args... args) : TaskInfo((TaskCounter*)nullptr, callable, args...){};

        template <typename Ret, typename... Args>
        explicit TaskInfo(Ret(*function)(Args...), Args... args) : TaskInfo((TaskCounter*)nullptr, function, args...){};

        template <class TCallable, typename... Args>
        explicit TaskInfo(TCallable* callable, Args... args) : TaskInfo((TaskCounter*)nullptr, callable, args...) {};

        template <class TClass, typename Ret, typename... Args>
        TaskInfo(Ret(TClass::* callable)(Args...), TClass* inst, Args... args) : TaskInfo((TaskCounter*)nullptr, callable, inst, args...) {};

        ~TaskInfo()
        {
            reset();
        }

        inline void setCounter(TaskCounter *newCounter)
        {
            counter = newCounter;
        }

        inline TaskCounter* getCounter() const
        {
            return counter;
        }

        void execute();

        TaskInfo& operator=(const TaskInfo& other)
        {
            if(&other == this)
            {
                return *this;
            }

            memcpy(buffer, other.buffer, bufferSize);
            counter = other.counter;

            return *this;
        }
    };

    enum class TaskPriority : u8
    {
        High,
        Normal,
        Low
    };

}
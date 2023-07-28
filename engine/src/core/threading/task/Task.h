#pragma once
#include "../../Types.h"

namespace core::threading
{
    class TaskScheduler;
    struct Task
    {
        Task() = default;

        template<class T,typename Ret ,typename ...Args>
        bool bind(T* object,Ret (T::*method)(Args...) , Args... args)
        {
            delegate = reinterpret_cast<core::BaseDelegate<std::any> *const>(new core::MethodDelegate(object,&T::method,args...));
            if(delegate == nullptr)
            {
                return false;
            }

            return true;
        }
        template<typename Ret ,typename ...Args>
        bool bind (Ret (*callableFunction)(Args...) , Args... args)
        {
            delegate = reinterpret_cast<core::BaseDelegate<std::any> *const>(new core::FunctionDelegate(callableFunction,args...));

            if(delegate == nullptr)
            {
                return false;
            }

            return true;
        }


        template<class T,typename Ret ,typename ...Args>
        HEXEN_INLINE bool operator==(Ret (T::*callableMethod)(Args...))
        {
            if(delegate == nullptr)
            {
                return false;
            }

            std::any object = callableMethod;
            return delegate->getId() == object.type().hash_code();
        }

        template<class T,typename Ret ,typename ...Args>
        HEXEN_INLINE bool operator!=(Ret (T::*callableMethod)(Args...))
        {
            if(delegate == nullptr)
            {
                return false;
            }

            std::any object = callableMethod;
            return delegate->getId() != object.type().hash_code();
        }
        template<typename Ret ,typename ...Args>
        HEXEN_INLINE bool operator==(Ret (*callableFunction)(Args...))
        {
            if(delegate == nullptr)
            {
                return false;
            }

            std::any object = callableFunction;
            return delegate->getId() == object.type().hash_code();
        }

        template<typename Ret ,typename ...Args>
        HEXEN_INLINE bool operator!=(Ret (*callableFunction)(Args...))
        {
            if(delegate == nullptr)
            {
                return false;
            }

            std::any object = callableFunction;
            return delegate->getId() != object.type().hash_code();
        }

        template<typename T ,typename ...Args>
        bool bind(T* object , Args... args)
        {
            delegate = reinterpret_cast<core::BaseDelegate<std::any> *const>(new core::FunctorDelegate(object,args...));

            if(delegate == nullptr)
            {
                return false;
            }

            return true;
        }


        template<typename T ,typename ...Args>
        HEXEN_INLINE bool operator==(T* functor)
        {
            if(delegate == nullptr)
            {
                return false;
            }

            std::any object = functor;
            return delegate->getId() == object.type().hash_code();
        }

        template<typename T ,typename ...Args>
        HEXEN_INLINE bool operator!=(T* functor)
        {
            if(delegate == nullptr)
            {
                return false;
            }

            std::any object = functor;
            return delegate->getId() != object.type().hash_code();
        }


        void execute()
        {
            if(delegate != nullptr)
            {
                delegate->execute();
            }
        }

        BaseDelegate<std::any> *delegate{nullptr};
        vptr ArgumentsData;
    };

    enum class TaskPriority
    {
        High,
        Normal,
    };
}

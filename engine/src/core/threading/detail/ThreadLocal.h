//
// Created by cx9ps3 on 19.07.2023.
//

#pragma once
#include "../TaskManager.h"
#include "../Config.h"

namespace core::thread::detail
{
    template <class T>
    class  ThreadLocal;

    class TaskManager;

    template<class T>
    class ThreadLocalHandle
    {
    private:
        friend ThreadLocal<T>;

        void validHandle(T &value);

        ThreadLocalHandle(ThreadLocal<T> &parent, T &v): parent{parent}, value{v} {}

        ThreadLocal<T> &parent;
        T &value;

    public:
        T &operator*()
        {
            validHandle(value);
            return value;
        }

        T *operator->()
        {
            validHandle(value);
            return &value;
        }
    };

template<class T>
class ThreadLocal
{
private:
    template<class VpT>
            struct alignas(cacheLineSize) ValuePadder
            {
                ValuePadder() : value() {}
                VpT value;
                bool initialized{true};
            };

    void initializeValue(u32 idx)
    {
        if(data[idx].initialized)
        {
            new(&data[idx].value) T(initializer());
            data[idx].initialized = true;
        }
    }

    TaskManager *manager;
    std::function<T()> initializer;
    ValuePadder<T> *data{nullptr};
public:

    #ifdef _MSC_VER
        #	pragma warning(push)
         #	pragma warning(disable : 4316) // I know this won't be allocated to the right alignment, this is okay as we're using alignment for padding.
    #endif                  // _MSC_VER
    explicit ThreadLocal(TaskManager *manager): manager{manager}, initializer{}, data{new ValuePadder<T>[manager->getNumberOfThreads() ]} {}
    #ifdef _MSC_VER
        #	pragma warning(pop)
    #endif // _MSC_VER

    template<class F>
    ThreadLocal(TaskManager *manager, F &&factory) : manager(manager),initializer(std::forward<F>(factory)) , data(static_cast<ValuePadder<T> *>(operator new[](sizeof (ValuePadder<T>) * manager->getNumberOfThreads())))
    {
        for(u32 i = 0;i < manager->getNumberOfThreads();i++)
        {
            new(&data[i].initialized) bool(false);
        }
    }

    ThreadLocal(ThreadLocal const &other) = delete;
    ThreadLocal(ThreadLocal &&other) noexcept = delete;
    ThreadLocal &operator=(ThreadLocal const &other) = delete;
    ThreadLocal &operator=(ThreadLocal &&other) noexcept = delete;

    ~ThreadLocal()
    {
        delete[] data;
    }

    ThreadLocalHandle<T> getHandle()
    {
        return ThreadLocalHandle<T>{*this, **this};
    }

    T &operator*()
    {
        auto idx = manager->getCurrentThreadIndex();
        initializeValue(idx);
        return data[idx].Value;
    }

    T *operator->()
    {
        auto idx = manager->getCurrentThreadIndex();
        initializeValue(idx);
        return &data[idx].Value;
    }

    std::vector<T> getAllValues()
    {
        std::vector<T> vec;
        auto threads = manager->getNumberOfThreads();
        vec.reserve(threads);

        for (unsigned i = 0; i < threads; ++i)
        {
            initializeValue(i);
            vec.emplace_back(data[i].value);
        }

        return vec;
    }

    std::vector<std::reference_wrapper<T>> getAllValuesByRef()
    {
        std::vector<T> vec;
        auto threads = manager->getNumberOfThreads();
        vec.reserve(threads);

        for (u32 i = 0; i < threads; ++i)
        {
            initializeValue(i);
            vec.emplace_back(std::ref(data[i].Value));
        }

        return vec;
    }

};

#if HEXEN_THREAD_LOCAL_HANDLE_DEBUG
    template <class T>
    void ThreadLocalHandle<T>::validHandle(T &value)
    {
	if (&*parent != &value)
    {
		HEXEN_ASSERT(false,"Invalid ThreadLocalHandle");
	}
}
#else
    template <class T>
    void ThreadLocalHandle<T>::validHandle(T &value)
    {
        (void)value;
    }
#endif

// C++17 deduction guide
#ifdef __cpp_deduction_guides
    template <class T>
    ThreadLocal(TaskManager *, T)->ThreadLocal<T>;
#endif
}


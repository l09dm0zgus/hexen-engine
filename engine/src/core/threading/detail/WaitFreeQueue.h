//
// Created by cx9ps3 on 19.07.2023.
//

#pragma once
#include "../../Types.h"
#include <vector>
#include <memory>
#include <atomic>
#include "../Config.h"

namespace core::threading::detail
{
    template<typename T>
    class WaitFreeQueue
    {
    private:
        constexpr static size startingCircularSize = 32;

        class CircularArray
        {
        private:
            std::vector<T> items;
            std::unique_ptr<CircularArray> previous;

        public:

            explicit CircularArray(size n) : items(n)
            {
                HEXEN_ASSERT( !(n == 0) && !(n & (n - 1)) , "n must be a power of 2");
            }

            size size() const
            {
                return items.size();
            }

            T get(core::size index)
            {
                return items[index & (size() -1)];
            }

            void put(core::size index,T x)
            {
                items[index & (size() -1)] = x;
            }

            CircularArray* grow(core::size top,core::size bottom)
            {
                auto *const newArray = new CircularArray(size() * 2);

                newArray->previous.reset(this);

                for (size_t i = top; i != bottom; i++)
                {
                    newArray->put(i, get(i));
                }
                return newArray;
            }

        };

#pragma warning(push)
#pragma warning(disable : 4324) // MSVC warning C4324: structure was padded due to alignment specifier
        alignas(cacheLineSize) std::atomic<u64> top;
        alignas(cacheLineSize) std::atomic<u64> bottom;
        alignas(cacheLineSize) std::atomic<CircularArray *> array;
#pragma warning(pop)

    public:

        void push(T value)
        {
            auto b  = bottom.load(std::memory_order_relaxed);
            auto t = top.load(std::memory_order_relaxed);
            auto a = array.load(std::memory_order_relaxed);

            if(b - t > a->size() - 1)
            {
                a = a->grow(t,b);

                array.store(a,std::memory_order_release);
            }

            a->put(b,value);

            std::atomic_thread_fence(std::memory_order_release);

            bottom.store(b + 1,std::memory_order_release);
        }

        bool pop(T* value)
        {
            auto b = bottom.load(std::memory_order_relaxed) - 1;

            auto a = array.load(std::memory_order_relaxed);

            bottom.store(b,std::memory_order_relaxed);

            std::atomic_thread_fence(std::memory_order_seq_cst);

            auto t = top.load(std::memory_order_relaxed);

            bool result{true};

            if(t <= b)
            {
                *value = a->get(b);
                if(t == b)
                {
                    if(!std::atomic_compare_exchange_strong_explicit(&top,&t,t+1,std::memory_order_seq_cst,std::memory_order_relaxed))
                    {
                        result = false;

                    }
                    bottom.store(b + 1,std::memory_order_relaxed);
                }
            }
            else
            {
                result = false;
                bottom.store(b + 1,std::memory_order_relaxed);

            }

            return result;
        }


        bool steal(T *const value)
        {
            auto t  = top.load(std::memory_order_acquire);

            std::atomic_thread_fence(std::memory_order_seq_cst);

            const auto b = bottom.load(std::memory_order_acquire);

            if(t < b)
            {
                auto  a = array.load(std::memory_order_consume);
                *value = a->get(t);
                return std::atomic_compare_exchange_strong_explicit(&top, &t, t + 1, std::memory_order_seq_cst, std::memory_order_relaxed);
            }

            return false;
        }

    };
}
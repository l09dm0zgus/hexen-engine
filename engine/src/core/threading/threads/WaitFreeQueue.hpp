
#pragma once

#include "../../Types.hpp"
#include "Config.hpp"

#include <atomic>
#include <memory>
#include <vector>

namespace hexen::engine::core::threading
{
    template <typename T>
    class WaitFreeQueue
    {
    private:
        constexpr static size_t startingCircularArraySize = 32;

    public:
        WaitFreeQueue(): top(1), bottom(1), array(new CircularArray(startingCircularArraySize)) {}

        WaitFreeQueue(WaitFreeQueue const &) = delete;
        WaitFreeQueue(WaitFreeQueue &&) noexcept = delete;
        WaitFreeQueue &operator=(WaitFreeQueue const &) = delete;
        WaitFreeQueue &operator=(WaitFreeQueue &&) noexcept = delete;

        ~WaitFreeQueue()
        {
            delete array.load(std::memory_order_relaxed);
        }

    private:
        class CircularArray
        {
        public:
            explicit CircularArray(size_t const n): items(n)
            {
                HEXEN_ASSERT(!(n == 0) && !(n & (n - 1)),"n must be a power of 2");
            }

        private:
            std::vector<T> items;
            std::unique_ptr<CircularArray> previous;

        public:
            [[nodiscard]] size_t size() const
            {
                return items.size();
            }

            T get(size_t const index)
            {
                return items[index & (size() - 1)];
            }

            void put(size_t const index, T x)
            {
                items[index & (size() - 1)] = x;
            }

            // Growing the array returns a new circular_array object and keeps a
            // linked list of all previous arrays. This is done because other threads
            // could still be accessing elements from the smaller arrays.
            CircularArray *grow(size_t const top, size_t const bottom)
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
        alignas(cacheLineSize) std::atomic<uint64_t> top;
        alignas(cacheLineSize) std::atomic<uint64_t> bottom;
        alignas(cacheLineSize) std::atomic<CircularArray *> array;
#pragma warning(pop)

    public:
        void push(T value)
        {
            auto b = bottom.load(std::memory_order_relaxed);
            auto t = top.load(std::memory_order_acquire);
            auto *a = this->array.load(std::memory_order_relaxed);

            if (b - t > a->size() - 1)
            {
                /* Full queue. */
                a = a->grow(t, b);
                array.store(a, std::memory_order_release);
            }
            a->put(b, value);

            std::atomic_thread_fence(std::memory_order_release);

            bottom.store(b + 1, std::memory_order_relaxed);
        }

        bool pop(T *value)
        {
            auto b = bottom.load(std::memory_order_relaxed) - 1;
            auto *const a = array.load(std::memory_order_relaxed);
            bottom.store(b, std::memory_order_relaxed);

            std::atomic_thread_fence(std::memory_order_seq_cst);

            auto t = top.load(std::memory_order_relaxed);
            bool result = true;
            if (t <= b)
            {
                /* Non-empty queue. */
                *value = a->get(b);
                if (t == b)
                {
                    /* Single last element in queue. */
                    if (!std::atomic_compare_exchange_strong_explicit(&top, &t, t + 1, std::memory_order_seq_cst, std::memory_order_relaxed))
                    {
                        /* Failed race. */
                        result = false;
                    }
                    bottom.store(b + 1, std::memory_order_relaxed);
                }
            } else
            {
                /* Empty queue. */
                result = false;
                bottom.store(b + 1, std::memory_order_relaxed);
            }

            return result;
        }

        bool steal(T *const value)
        {
            auto t = top.load(std::memory_order_acquire);

            std::atomic_thread_fence(std::memory_order_seq_cst);

            auto const b = bottom.load(std::memory_order_acquire);
            if (t < b)
            {
                /* Non-empty queue. */
                auto *const a = array.load(std::memory_order_consume);
                *value = a->get(t);
                return std::atomic_compare_exchange_strong_explicit(&top, &t, t + 1, std::memory_order_seq_cst, std::memory_order_relaxed);
            }

            return false;
        }
    };
}

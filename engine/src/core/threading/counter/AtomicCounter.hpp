
#pragma once

#include "BaseCounter.hpp"

namespace hexen::engine::core::threading
{
    class FullAtomicCounter : public BaseCounter
    {

    public:

        explicit FullAtomicCounter(TaskScheduler *taskScheduler, u32 const initialValue = 0, u32 const fiberSlots = NUMBER_OF_WAITING_FIBER_SLOTS): BaseCounter(taskScheduler, initialValue, fiberSlots){}

        FullAtomicCounter(FullAtomicCounter const &) = delete;
        FullAtomicCounter(FullAtomicCounter &&) noexcept = delete;
        FullAtomicCounter &operator=(FullAtomicCounter const &) = delete;
        FullAtomicCounter &operator=(FullAtomicCounter &&) noexcept = delete;
        ~FullAtomicCounter() = default;

    public:

        u32 load(std::memory_order const memoryOrder = std::memory_order_seq_cst)
        {
            lock.fetch_add(1U, std::memory_order_seq_cst);

            auto result = value.load(memoryOrder);

            lock.fetch_sub(1U, std::memory_order_seq_cst);
            return result;
        }

        void store(u32 const x, std::memory_order const memoryOrder = std::memory_order_seq_cst)
        {
            lock.fetch_add(1U, std::memory_order_seq_cst);

            value.store(x, memoryOrder);
            checkWaitingFibers(x);

            lock.fetch_sub(1U, std::memory_order_seq_cst);
        }

        u32 fetchAdd(u32 const x, std::memory_order const memoryOrder = std::memory_order_seq_cst)
        {
            lock.fetch_add(1U, std::memory_order_seq_cst);

            const auto previous = value.fetch_add(x, memoryOrder);
            checkWaitingFibers(previous + x);

            lock.fetch_sub(1U, std::memory_order_seq_cst);
            return previous;
        }

        u32 fetchSub(u32 const x, std::memory_order const memoryOrder = std::memory_order_seq_cst)
        {
            lock.fetch_add(1U, std::memory_order_seq_cst);

            const auto previous = value.fetch_sub(x, memoryOrder);
            checkWaitingFibers(previous - x);

            lock.fetch_sub(1U, std::memory_order_seq_cst);
            return previous;
        }


        bool compareExchange(u32 expectedValue, u32 const newValue, std::memory_order const memoryOrder = std::memory_order_seq_cst)
        {
            lock.fetch_add(1U, std::memory_order_seq_cst);

            auto const success = value.compare_exchange_strong(expectedValue, newValue, memoryOrder);
            if (success)
            {
                checkWaitingFibers(newValue);
            }

            lock.fetch_sub(1U, std::memory_order_seq_cst);
            return success;
        }
    };

    class AtomicFlag : public BaseCounter
    {
    public:

        explicit AtomicFlag(TaskScheduler *taskScheduler, u32 const initialValue = 0, u32 const fiberSlots = NUMBER_OF_WAITING_FIBER_SLOTS): BaseCounter(taskScheduler, initialValue, fiberSlots){}

        AtomicFlag(AtomicFlag const &) = delete;
        AtomicFlag(AtomicFlag &&) noexcept = delete;
        AtomicFlag &operator=(AtomicFlag const &) = delete;
        AtomicFlag &operator=(AtomicFlag &&) noexcept = delete;
        ~AtomicFlag() = default;

    public:
        bool set(std::memory_order const memoryOrder = std::memory_order_seq_cst)
        {
            return value.exchange(1U, memoryOrder) == 0;
        }

        bool Clear(std::memory_order const memoryOrder = std::memory_order_seq_cst)
        {
            lock.fetch_add(1U, std::memory_order_seq_cst);

            const auto success = value.exchange(0U, memoryOrder) == 1;
            if (!success)
            {
                lock.fetch_sub(1U, std::memory_order_seq_cst);
                return false;
            }
            checkWaitingFibers(0U);

            lock.fetch_sub(1U, std::memory_order_seq_cst);
            return true;
        }
    };
}

//
// Created by cx9ps3 on 19.07.2023.
//

#pragma once
#include "BaseCounter.h"

namespace core::threading
{
    class AtomicCounter : public BaseCounter
    {
    public:
        explicit AtomicCounter(TaskManager *taskManager,u32 initialValue,u32 fiberSlots = NUMBER_OF_WAITING_FIBERS) : BaseCounter(taskManager,initialValue,fiberSlots) {}

        AtomicCounter(AtomicCounter const &) = delete;
        AtomicCounter(AtomicCounter &&) noexcept = delete;
        AtomicCounter &operator=(AtomicCounter const &) = delete;
        AtomicCounter &operator=(AtomicCounter &&) noexcept = delete;
        ~AtomicCounter() = default;

        u32 load(const std::memory_order &order = std::memory_order_seq_cst)
        {
            lock.fetch_add(1u,std::memory_order_seq_cst);

            auto result = counter.load(order);

            lock.fetch_sub(1u,std::memory_order_seq_cst);

            return result;
        }

        void store(u32 x,const std::memory_order &order = std::memory_order_seq_cst)
        {
            lock.fetch_add(1u,std::memory_order_seq_cst);

            counter.store(x,order);

            checkWaitingFibers(x);

            lock.fetch_sub(1u,std::memory_order_seq_cst);
        }

        u32 fetchAdd(u32 x,const std::memory_order &order = std::memory_order_seq_cst)
        {
            lock.fetch_add(1u,std::memory_order_seq_cst);

            auto  result = counter.fetch_add(x,order);

            checkWaitingFibers(x + result);

            lock.fetch_sub(1u,std::memory_order_seq_cst);

            return result;
        }

        u32 fetchSub(u32 x,const std::memory_order &order = std::memory_order_seq_cst)
        {
            lock.fetch_add(1u,std::memory_order_seq_cst);

            auto  result = counter.fetch_sub(x,order);

            checkWaitingFibers(result - x);

            lock.fetch_sub(1u,std::memory_order_seq_cst);

            return result;
        }

        bool compareExchange(u32 expectedValue,u32 newValue,const std::memory_order &order = std::memory_order_seq_cst)
        {
            lock.fetch_add(1u,std::memory_order_seq_cst);

            auto  result = counter.compare_exchange_strong(expectedValue, newValue ,order);

            if(result)
            {
                checkWaitingFibers(newValue);

            }

            lock.fetch_sub(1u,std::memory_order_seq_cst);

            return result;
        }

    };

    class AtomicFlag : public BaseCounter
    {
    public:
        explicit AtomicFlag(TaskManager *taskManager,u32 initialValue,u32 fiberSlots = NUMBER_OF_WAITING_FIBERS) : BaseCounter(taskManager,initialValue,fiberSlots) {}

        AtomicFlag(AtomicFlag const &) = delete;
        AtomicFlag(AtomicFlag &&) noexcept = delete;
        AtomicFlag &operator=(AtomicFlag const &) = delete;
        AtomicFlag &operator=(AtomicFlag &&) noexcept = delete;
        ~AtomicFlag() = default;

        bool set(const std::memory_order &order =  std::memory_order_seq_cst )
        {
            return counter.exchange(1U,order) == 0;
        }

        bool clear(const std::memory_order &order =  std::memory_order_seq_cst )
        {
            lock.fetch_add(1u,std::memory_order_seq_cst);

            auto  result = counter.exchange(0u,order) == 1;

            if(result)
            {
                lock.fetch_sub(1u,std::memory_order_seq_cst);
                return false;
            }

            lock.fetch_sub(1u,std::memory_order_seq_cst);

            return true;
        }
    };
}
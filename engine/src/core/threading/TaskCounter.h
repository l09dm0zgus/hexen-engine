//
// Created by cx9ps3 on 20.07.2023.
//

#pragma once
#include "BaseCounter.h"

namespace core::threading
{
    class TaskCounter : public BaseCounter
    {
    public:
        explicit TaskCounter(TaskManager *manager,u32 initialValue = 0 ,u32 fiberSlots = BaseCounter::NUMBER_OF_WAITING_FIBERS) : BaseCounter(manager,initialValue,fiberSlots) {}

        TaskCounter(TaskCounter const &) = delete;
        TaskCounter(TaskCounter &&) noexcept = delete;
        TaskCounter &operator=(TaskCounter const &) = delete;
        TaskCounter &operator=(TaskCounter &&) noexcept = delete;
        ~TaskCounter() = default;

        void add(u32 x)
        {
            counter.fetch_add(x);
        }

        void decrement()
        {
            lock.fetch_add(1U, std::memory_order_seq_cst);

            const auto previous = counter.fetch_sub(1U, std::memory_order_seq_cst);
            const auto newValue = previous - 1;

            if (newValue == 0)
            {
                checkWaitingFibers(newValue);
            }

            lock.fetch_sub(1U, std::memory_order_seq_cst);
        }
    };
}
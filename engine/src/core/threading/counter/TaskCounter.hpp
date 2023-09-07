#pragma once

#include "BaseCounter.hpp"

namespace hexen::engine::core::threading
{
    class TaskScheduler;

    class TaskCounter : public BaseCounter {

    public:

        explicit TaskCounter(TaskScheduler *taskScheduler, u32 const initialValue = 0, u32 const fiberSlots = NUMBER_OF_WAITING_FIBER_SLOTS): BaseCounter(taskScheduler, initialValue, fiberSlots) {}

        TaskCounter(TaskCounter const &) = delete;
        TaskCounter(TaskCounter &&) noexcept = delete;
        TaskCounter &operator=(TaskCounter const &) = delete;
        TaskCounter &operator=(TaskCounter &&) noexcept = delete;
        ~TaskCounter() = default;

    public:

        void add(unsigned const x)
        {
            value.fetch_add(x, std::memory_order_seq_cst);
        }


        void decrement()
        {
            lock.fetch_add(1U, std::memory_order_seq_cst);

            const auto previous = value.fetch_sub(1U, std::memory_order_seq_cst);
            const auto newValue = previous - 1;

            // TaskCounters are only allowed to wait on 0, so we only need to check when newValue would be zero
            if (newValue == 0)
            {
                checkWaitingFibers(newValue);
            }

            lock.fetch_sub(1U, std::memory_order_seq_cst);
        }
    };
}

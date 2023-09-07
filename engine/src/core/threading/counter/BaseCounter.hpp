#pragma once

#include <atomic>
#include <limits>
#include "../../Types.hpp"

namespace hexen::engine::core::threading
{

    class TaskScheduler;

    class BaseCounter
    {

    public:

        static constexpr u32 NUMBER_OF_WAITING_FIBER_SLOTS = 4;

        explicit BaseCounter(TaskScheduler *taskScheduler, u32 initialValue = 0, u32 fiberSlots = NUMBER_OF_WAITING_FIBER_SLOTS);

        BaseCounter(BaseCounter const &) = delete;
        BaseCounter(BaseCounter &&) noexcept = delete;
        BaseCounter &operator=(BaseCounter const &) = delete;
        BaseCounter &operator=(BaseCounter &&) noexcept = delete;
        ~BaseCounter();

    protected:
        TaskScheduler *taskScheduler;
        std::atomic<u32> value;
        std::atomic<u32> lock;

        std::atomic<bool> *freeSlots;
        std::atomic<bool> freeSlotsStorage[NUMBER_OF_WAITING_FIBER_SLOTS];

        struct WaitingFiberBundle
        {
            WaitingFiberBundle();

            std::atomic<bool> inUse;
            vptr fiberBundle{nullptr};
            u32 targetValue{0};

            u32 pinnedThreadIndex;
        };

        WaitingFiberBundle *waitingFibers;
        WaitingFiberBundle waitingFibersStorage[NUMBER_OF_WAITING_FIBER_SLOTS];


        unsigned fiberSlots;

        friend class TaskScheduler;

    protected:
        bool addFiberToWaitingList(vptr fiberBundle, u32 targetValue, u32 pinnedThreadIndex = std::numeric_limits<u32>::max());

        void checkWaitingFibers(u32 value);
    };
}

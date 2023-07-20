//
// Created by cx9ps3 on 14.07.2023.
//

#pragma once

#include <atomic>
#include "../Types.h"

namespace core::threading
{
    class TaskManager;
    class BaseCounter
    {
    public:
        static constexpr const u8 NUMBER_OF_WAITING_FIBERS = 4;
    protected:

        TaskManager *manager;
        std::atomic<u32> counter{0};
        std::atomic<u32> lock{0};

        std::atomic<bool> *freeSlots{nullptr};
        std::atomic<bool> freeSlotsStorage[NUMBER_OF_WAITING_FIBERS];

        struct WaitingFiberBundle
        {
            WaitingFiberBundle();

            std::atomic<bool> inUse;

            vptr fiberBundle{nullptr};

            u32 targetValue{0};

            u32 pinnedThreadIndex;

        };

        WaitingFiberBundle *waitingFibers{nullptr};
        WaitingFiberBundle waitingFiberStorage[NUMBER_OF_WAITING_FIBERS];

        u32 fiberSlots{0};

        friend  class TaskManager;

        bool addFiberToWaitingList(vptr fiberBundle,u32 targetValue, u32 pinnedThreadIndex = std::numeric_limits<u32>::max());

        void checkWaitingFibers(u32 value);

    public:
       explicit BaseCounter(TaskManager* manager,u32 initialValue = 0, u32 fiberSlots = NUMBER_OF_WAITING_FIBERS);

        BaseCounter(BaseCounter const &) = delete;
        BaseCounter(BaseCounter &&) noexcept = delete;
        BaseCounter &operator=(BaseCounter const &) = delete;
        BaseCounter &operator=(BaseCounter &&) noexcept = delete;
        ~BaseCounter();

    };
}

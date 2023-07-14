//
// Created by cx9ps3 on 14.07.2023.
//

#include "TaskCounter.h"

core::threading::detail::BaseCounter::BaseCounter(core::threading::Manager *manager, core::u8 numberOfWaitingFibers,core::threading::detail::BaseCounter::WaitingFibers *waitingFibers,std::atomic_bool *freeWaitingSlots) : manager(manager) , nubmberOfWaitingFibers(numberOfWaitingFibers),waitingFibers(waitingFibers),freeWaitingSlots(freeWaitingSlots)
{

}

void core::threading::detail::BaseCounter::initializeWaitingFibers()
{
    for(u8 i = 0;i < nubmberOfWaitingFibers;i++)
    {
        freeWaitingSlots[i].store(true);
    }
}

void core::threading::detail::BaseCounter::checkWaitingFibers(core::u32 value)
{
    for(u64 i = 0;i < nubmberOfWaitingFibers;i++)
    {
        if(freeWaitingSlots[i].load(std::memory_order_acquire))
        {
            continue;
        }

        auto waitingSlot = &waitingFibers[i];
        if(waitingSlot->inUse.load(std::memory_order_acquire))
        {
            continue;
        }

        if(waitingSlot->targetValue == value)
        {
            bool expected{false};

            if(!std::atomic_compare_exchange_strong_explicit(&waitingSlot->inUse,&expected, true,std::memory_order_seq_cst,std::memory_order_relaxed))
            {
                continue;
            }

            //manager->getCurrentTLS()->readyFibers.emplace_back(waitingSlot->fiberIndex, waitingSlot->fiberStored);
            freeWaitingSlots[i].store(true, std::memory_order_release);
        }
    }
}

core::u32 core::threading::detail::BaseCounter::increment(core::u32 by)
{
    auto previous = counter.fetch_add(by);
    checkWaitingFibers(previous + by);
    return previous;
}

core::u32 core::threading::detail::BaseCounter::decrement(core::u32 by)
{
    auto previous = counter.fetch_add(by);
    checkWaitingFibers(previous - by);
    return previous;
}

core::u32 core::threading::detail::BaseCounter::getValue() const
{
    return counter.load(std::memory_order_seq_cst);
}

bool core::threading::detail::BaseCounter::addWaitingFiber(core::u16 fiberIndex, core::u32 targetValue,std::atomic_bool *fiberStored) {
    for (u8 i = 0; i < nubmberOfWaitingFibers; i++) {
        // Acquire Free Waiting Slot
        bool expected = true;
        if (!std::atomic_compare_exchange_strong_explicit(&freeWaitingSlots[i], &expected, false,
                                                          std::memory_order_seq_cst, std::memory_order_relaxed)) {
            continue;
        }

        // Setup Slot
        auto slot = &waitingFibers[i];
        slot->fiberIndex = fiberIndex;
        slot->fiberStored = fiberStored;
        slot->targetValue = targetValue;

        slot->inUse.store(false);

        // Check if we are done already
        auto c = counter.load(std::memory_order_relaxed);

        if (slot->inUse.load(std::memory_order_acquire)) {
            return false;
        }

        if (slot->targetValue == counter) {
            expected = false;
            if (!std::atomic_compare_exchange_strong_explicit(&slot->inUse, &expected, true, std::memory_order_seq_cst,
                                                              std::memory_order_relaxed)) {
                return false;
            }

            freeWaitingSlots[i].store(true, std::memory_order_release);
            return true;
        }

        return false;
    }
    return false;
}

core::threading::TaskCounter::TaskCounter(core::threading::Manager *manager) : detail::BaseCounter(manager, MAX_WAITING, waitingFibers, freeWaitingSlots)
{
    initializeWaitingFibers();
}

core::threading::detail::TinyCounter::TinyCounter(core::threading::Manager *manager) : detail::BaseCounter(manager,1,&waitingFiber,&freeWaitingSlot)
{
    initializeWaitingFibers();
}

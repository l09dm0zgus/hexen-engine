//
// Created by cx9ps3 on 14.07.2023.
//

#include "BaseCounter.h"
#include "TaskManager.h"
#include <thread>

core::threading::BaseCounter::BaseCounter(core::threading::TaskManager *manager, core::u32 initialValue,core::u32 fiberSlots) : manager(manager),counter(initialValue) , freeSlots(freeSlotsStorage) , freeSlotsStorage() , waitingFibers(waitingFiberStorage) , fiberSlots(fiberSlots)
{
    if(fiberSlots  > NUMBER_OF_WAITING_FIBERS)
    {
        freeSlots = new std::atomic<bool>[fiberSlots];
        waitingFibers = new WaitingFiberBundle[fiberSlots];
    }

    for(u32 i = 0;i < fiberSlots; i++)
    {
        freeSlots[i].store(true);
        waitingFibers[i].inUse.store(true);
    }

}

core::threading::BaseCounter::~BaseCounter()
{
    while (lock.load(std::memory_order_relaxed) > 0)
    {
        std::this_thread::yield();
    }

    if (fiberSlots > NUMBER_OF_WAITING_FIBERS)
    {
        delete[] freeSlots;
        delete[] waitingFibers;
    }
}

bool core::threading::BaseCounter::addFiberToWaitingList(core::vptr fiberBundle, core::u32 targetValue,core::u32 pinnedThreadIndex)
{
    for(u32 i = 0;i < fiberSlots; i++)
    {
        bool expected{true};
        if(!std::atomic_compare_exchange_strong_explicit(&freeSlots[i],&expected, false,std::memory_order_seq_cst,std::memory_order_relaxed))
        {
            continue;
        }

        waitingFibers[i].fiberBundle = fiberBundle;
        waitingFibers[i].targetValue = targetValue;
        waitingFibers[i].inUse.store(false,std::memory_order_seq_cst);

        auto value = counter.load(std::memory_order_relaxed);

        if (waitingFibers[i].inUse.load(std::memory_order_acquire))
        {
            return false;
        }

        if(waitingFibers[i].targetValue == value)
        {
            expected = false;

            if(!std::atomic_compare_exchange_strong_explicit(&waitingFibers[i].inUse,&expected, true,std::memory_order_seq_cst,std::memory_order_relaxed))
            {
                return false;
            }

            freeSlots[i].store(true,std::memory_order_release);

            return true;

        }


    }

    HEXEN_ASSERT(false,"All the waiting fiber slots are full. Not able to add another wait.\n"
               "Increase the value of fiberSlots in the constructor or modify your algorithm to use less waits on the same counter");
    return false;
}

void core::threading::BaseCounter::checkWaitingFibers(core::u32 value)
{
    for(u32 i = 0;i < fiberSlots;i++)
    {
        if(freeSlots[i].load(std::memory_order_acquire))
        {
            continue;
        }

        if(waitingFibers[i].inUse.load(std::memory_order_acquire))
        {
            continue;
        }

        if(waitingFibers[i].targetValue == value)
        {
            bool expected = false;

            if(!std::atomic_compare_exchange_strong_explicit(&waitingFibers[i].inUse,&expected, true,std::memory_order_seq_cst,std::memory_order_relaxed))
            {
                continue;
            }

            manager->addReadyFiber(waitingFibers[i].pinnedThreadIndex, reinterpret_cast<TaskManager::ReadyFiberBundle *>(waitingFibers[i].fiberBundle));

            freeSlots[i].store(true,std::memory_order_release);

        }

    }
}

core::threading::BaseCounter::WaitingFiberBundle::WaitingFiberBundle() : inUse(true) , pinnedThreadIndex(std::numeric_limits<u32>::max())
{
}

#include "BaseCounter.h"

#include "../task/TaskScheduler.h"

#include <thread>

namespace core::threading
{
    BaseCounter::BaseCounter(TaskScheduler *const taskScheduler, u32 initialValue, u32 fiberSlots): taskScheduler(taskScheduler), value(initialValue), lock(0),freeSlots(freeSlotsStorage), freeSlotsStorage(),waitingFibers(waitingFibersStorage),fiberSlots(fiberSlots)
    {
        // Small Vector Optimization
        if (fiberSlots > NUMBER_OF_WAITING_FIBER_SLOTS)
        {
            freeSlots = new std::atomic<bool>[fiberSlots];
            waitingFibers = new WaitingFiberBundle[fiberSlots];
        }


        for (u32 i = 0; i < fiberSlots; ++i)
        {
            freeSlots[i].store(true);

            // We initialize inUse to true to prevent checkWaitingFibers() from checking garbage
            // data when we are adding a new fiber to the wait list in addFiberToWaitingList()
            // For this same reason, when we set a slot to be free (ie. freeSlots[i] = true), we
            // keep inUse == true
            waitingFibers[i].inUse.store(true);
        }
    }

    BaseCounter::~BaseCounter()
    {
        // We can't destroy the counter until all other threads have left the member functions
        while (lock.load(std::memory_order_relaxed) > 0)
        {
            std::this_thread::yield();
        }

        if (fiberSlots > NUMBER_OF_WAITING_FIBER_SLOTS)
        {
            delete[] freeSlots;
            delete[] waitingFibers;
        }
    }

    BaseCounter::WaitingFiberBundle::WaitingFiberBundle(): inUse(true), pinnedThreadIndex(std::numeric_limits<u32>::max())
    {
    }

    bool BaseCounter::addFiberToWaitingList(vptr fiberBundle, u32 targetValue, u32 const pinnedThreadIndex)
    {
        for (u32 i = 0; i < fiberSlots; ++i)
        {
            bool expected = true;
            // Try to acquire the slot
            if (!std::atomic_compare_exchange_strong_explicit(&freeSlots[i], &expected, false, std::memory_order_seq_cst, std::memory_order_relaxed))
            {
                // Failed the race or the slot was already full
                continue;
            }

            // We found a free slot
            waitingFibers[i].fiberBundle = fiberBundle;
            waitingFibers[i].targetValue = targetValue;
            waitingFibers[i].pinnedThreadIndex = pinnedThreadIndex;
            // We have to use memory_order_seq_cst here instead of memory_order_acquire to prevent
            // later loads from being re-ordered before this store
            waitingFibers[i].inUse.store(false, std::memory_order_seq_cst);

            // Events are now being tracked

            // Now we do a check of the waiting fiber, to see if we reached the target value while we were storing
            // everything
            auto const v = value.load(std::memory_order_relaxed);
            if (waitingFibers[i].inUse.load(std::memory_order_acquire))
            {
                return false;
            }

            if (waitingFibers[i].targetValue == v)
            {
                expected = false;
                // Try to acquire inUse
                if (!std::atomic_compare_exchange_strong_explicit(&waitingFibers[i].inUse, &expected, true, std::memory_order_seq_cst, std::memory_order_relaxed))
                {
                    // Failed the race. Another thread got to it first.
                    return false;
                }
                // Signal that the slot is now free
                // Leave IneUse == true
                freeSlots[i].store(true, std::memory_order_release);

                return true;
            }

            return false;
        }

        // BARF. We ran out of slots
        HEXEN_ASSERT(false,"All the waiting fiber slots are full. Not able to add another wait.\n""Increase the value of fiberSlots in the constructor or modify your algorithm to use less waits on the same counter");
        return false;
    }

    void BaseCounter::checkWaitingFibers(u32 const value)
    {
        for (u32 i = 0; i < fiberSlots; ++i)
        {
            // Check if the slot is full
            if (freeSlots[i].load(std::memory_order_acquire))
            {
                continue;
            }
            // Check if the slot is being modified by another thread
            if (waitingFibers[i].inUse.load(std::memory_order_acquire))
            {
                continue;
            }

            // Do the actual value check
            if (waitingFibers[i].targetValue == value)
            {
                bool expected = false;
                // Try to acquire inUse
                if (!std::atomic_compare_exchange_strong_explicit(&waitingFibers[i].inUse, &expected, true, std::memory_order_seq_cst, std::memory_order_relaxed))
                {
                    // Failed the race. Another thread got to it first
                    continue;
                }

                taskScheduler->addReadyFiber(waitingFibers[i].pinnedThreadIndex,
                                             reinterpret_cast<TaskScheduler::ReadyFiberBundle *>(waitingFibers[i].fiberBundle));
                // Signal that the slot is free
                // Leave inUse == true
                freeSlots[i].store(true, std::memory_order_release);
            }
        }
    }
}

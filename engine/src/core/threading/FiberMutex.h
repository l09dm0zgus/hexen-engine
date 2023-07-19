//
// Created by cx9ps3 on 19.07.2023.
//

#pragma once
#include "../Types.h"
#include "AtomicCounter.h"
#include "TaskManager.h"
#include "Config.h"

namespace core::threading
{
    class FiberMutex
    {
    public:
        explicit FiberMutex(TaskManager *manager,u32 fiberSlots = BaseCounter::NUMBER_OF_WAITING_FIBERS) : ableToSpin(manager->getNumberOfThreads() > 1) , taskManager(manager),atomicCounter(manager,0,fiberSlots)
        {

        }

        FiberMutex(FiberMutex&& mutex) = delete;
        FiberMutex(const FiberMutex& mutex) = delete;
        FiberMutex& operator=(FiberMutex&& mutex) = delete;
        FiberMutex& operator=(const FiberMutex& mutex) = delete;
        ~FiberMutex() = default;

        void lock(bool pinnedToThread = false)
        {
            while (true)
            {
                if(atomicCounter.set(std::memory_order_acq_rel))
                {
                    return;
                }

                taskManager->waitForCounter(&atomicCounter,pinnedToThread);

            }
        }

        void lockSpin(bool pinToThread = false,u32 iterations = 10000)
        {
            if(!ableToSpin)
            {
                lock(pinToThread);
                return;
            }

           for(u32 i = 0;i < iterations; i++)
            {
                if(atomicCounter.set(std::memory_order_acq_rel))
                {
                    return;
                }

                HEXEN_PAUSE();
            }

            lock(pinToThread);

        }

        void lockSpinInfinite(bool pinnedToThread = false)
        {
            if(!ableToSpin)
            {
                lock(pinnedToThread);
                return;
            }
            while (true)
            {
                if(atomicCounter.set(std::memory_order_acq_rel))
                {
                    return;
                }

                HEXEN_PAUSE();
            }
        }

        bool tryLock()
        {
            return atomicCounter.set(std::memory_order_acq_rel);
        }

        void unlock()
        {
            if (!atomicCounter.Clear(std::memory_order_acq_rel))
            {
                HEXEN_ASSERT(false,"Error: Mutex was unlocked by another fiber or was double unlocked.");
            }
        }


    private:
        bool ableToSpin{};
        TaskManager *taskManager;
        AtomicCounter atomicCounter;

    };

    enum class FiberMutexLockBehavior : u8
    {
        Traditional,
        Spin,
        SpinInfinite,
    };

    class LockWrapper
    {
    public:
        LockWrapper(FiberMutex& mutex,FiberMutexLockBehavior behavior,bool pinToThread = false,u32 spinItarations = 1000) : mutex(mutex) , pinToThread(pinToThread) , behavior(behavior) , spinIterations(spinItarations) {}

        void lock()
        {
            switch (behavior)
            {
                case FiberMutexLockBehavior::Traditional:
                    mutex.lock(pinToThread);
                    break;
                case FiberMutexLockBehavior::Spin:
                    mutex.lockSpin(pinToThread,spinIterations);
                case FiberMutexLockBehavior::SpinInfinite:
                    mutex.lockSpinInfinite(pinToThread);
                    break;
            }
        }

        bool tryLock()
        {
            return  mutex.tryLock();
        }

        void unlock() const
        {
            mutex.unlock();
        }

    private:
        FiberMutex &mutex;
        bool pinToThread{};
        FiberMutexLockBehavior behavior;
        u32 spinIterations;
    };
}

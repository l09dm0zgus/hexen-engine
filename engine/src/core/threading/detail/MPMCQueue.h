//
// Created by cx9ps3 on 14.07.2023.
//

#ifndef HEXENEDITOR_MPMCQUEUE_H
#define HEXENEDITOR_MPMCQUEUE_H

#include "../../Types.h"
#include <atomic>
#include <assert.h>

namespace core::threading::detail
{
    // Source: Dmitry Vyukov's MPMC
    // http://www.1024cores.net/home/lock-free-algorithms/queues/bounded-mpmc-queue

    template<typename T>
    class MPMCQueue
    {
    public:
        explicit MPMCQueue(u64 bufferSize): buffer(new Cell[bufferSize]) , bufferMask(bufferSize - 1)
        {
            assert((bufferSize >= 2) && ((bufferSize & (bufferSize - 1)) == 0));

            for (size_t i = 0; i != bufferSize; i += 1)
            {
                buffer[i].sequence.store(i, std::memory_order_relaxed);
            }

            enqueuePosition.store(0, std::memory_order_relaxed);
            dequeuePosition.store(0, std::memory_order_relaxed);
        }

        ~MPMCQueue()
        {
            delete[] buffer;
        }

        bool enqueue(const T& data)
        {
            Cell* cell;
            u64 position = enqueuePosition.load(std::memory_order_relaxed);

            for (;;)
            {
                cell = &buffer[position & bufferMask];
                u64 sequence = cell->sequence.load(std::memory_order_acquire);
                intptr_t difference = (intptr_t)sequence - (intptr_t)position;

                if (difference == 0)
                {
                    if (enqueuePosition.compare_exchange_weak(position, position + 1, std::memory_order_relaxed))
                    {
                        break;
                    }
                }
                else if (difference < 0)
                {
                    return false;
                }
                else
                {
                    position = enqueuePosition.load(std::memory_order_relaxed);
                }
            }

            cell->data = data;
            cell->sequence.store(position + 1, std::memory_order_release);

            return true;
        }

        bool dequeue(T& data)
        {
            Cell* cell;
            u64 position = dequeuePosition.load(std::memory_order_relaxed);
            for (;;)
            {
                cell = &buffer[position & bufferMask];
                u64 sequence = cell->sequence.load(std::memory_order_acquire);
                intptr_t difference = (intptr_t)sequence - (intptr_t)(position + 1);

                if (difference == 0)
                {
                    if (dequeuePosition.compare_exchange_weak(position, position + 1, std::memory_order_relaxed))
                    {
                        break;
                    }
                }
                else if (difference < 0)
                {
                    return false;
                }
                else
                {
                    position = dequeuePosition.load(std::memory_order_relaxed);

                }
            }

            data = cell->data;
            cell->sequence.store(position + bufferMask + 1, std::memory_order_release);

            return true;
        }

    private:
        struct Cell
        {
            std::atomic<size_t>   sequence;
            T                     data;
        };

        static u64 const cacheLineSize  = 64;
        using CacheLinePad = char[cacheLineSize];

        CacheLinePad pad0;
        Cell* const buffer{nullptr};
        u64 const bufferMask{0};

        CacheLinePad pad1;
        std::atomic<u64> enqueuePosition;
        CacheLinePad pad2;

        std::atomic<u64> dequeuePosition;
        CacheLinePad pad3;
    };
}

#endif //HEXENEDITOR_MPMCQUEUE_H

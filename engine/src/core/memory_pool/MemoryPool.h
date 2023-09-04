//
// Created by cx9ps3 on 09.05.2023.
//

#pragma once

#include "../Types.h"
#include <vector>
namespace core::mem
{
    class MemoryPool
    {
        struct Allocation
        {
            u8 freeFlag{0};
            u64 allocatedBytes{0};
            u64 occupiedBytes{0};
            vptr address{nullptr};
        };
    public:
        explicit MemoryPool(u64 size);
        ~MemoryPool();
        vptr allocate(u64 size);
        void free(vptr address) noexcept;

        MemoryPool(MemoryPool&& memoryPool) = delete;
        MemoryPool(const MemoryPool& memoryPool) = delete;

        MemoryPool& operator=(MemoryPool&& memoryPool) = delete;
        MemoryPool& operator=(const MemoryPool &memoryPool) = delete;
    private:
        inline void showLogForAllocation(const Allocation &allocation);
        std::vector<Allocation> allocations;
        u64 size;
        vptr memory;
        vptr lastAddress;
        vptr maxAddress;
    };
}

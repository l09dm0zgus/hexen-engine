//
// Created by cx9ps3 on 09.05.2023.
//

#ifndef BATTLEBLAZE_MEMORYPOOL_H
#define BATTLEBLAZE_MEMORYPOOL_H
#include "../Types.h"
#include <vector>
namespace core::mem
{
    class MemoryPool
    {
        struct Allocation
        {
            u8 freeFlag;
            u64 allocatedBytes;
            u64 occupiedBytes;
            vptr address;
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

#endif //BATTLEBLAZE_MEMORYPOOL_H

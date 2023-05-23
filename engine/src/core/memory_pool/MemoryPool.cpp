//
// Created by cx9ps3 on 09.05.2023.
//

#include "MemoryPool.h"
#include <SDL3/SDL.h>
#include <malloc.h>
#include <algorithm>

core::mem::MemoryPool::MemoryPool(u64 size) : size(size)
{
    memory = malloc(size);
    lastAddress = memory;
    maxAddress = (vptr) (((u64)memory) + (size));
    SDL_Log("Allocated memory in pool : %lu bytes.\nMemory address : %p.\n",size,memory);
}

void core::mem::MemoryPool::free(vptr address) noexcept
{
    auto iterator = std::find_if(allocations.begin(),allocations.end(),[address = address](const auto &allocation)
    {
      return allocation.address == address;
    });
    if(iterator != allocations.end())
    {
        SDL_Log("Freed allocation from address: %p\n.Returned memory to pool : %lu.\n",address,iterator->occupiedBytes );
        iterator->freeFlag = 1u;
        iterator->occupiedBytes = 0;
    }
}

core::mem::MemoryPool::~MemoryPool()
{
    free(memory);
    SDL_Log("Freed memory from pool  address : %p.Size of freed memory: %lu.\n",memory,size);
}

core::vptr core::mem::MemoryPool::allocate(u64 allocationSize)
{
    auto freeAllocationIterator = std::find_if(allocations.begin(),allocations.end(),[size = allocationSize](const auto &allocation)
    {
       return allocation.freeFlag == 1u && allocation.allocatedBytes >= size;
    });

    if(freeAllocationIterator != allocations.end())
    {
        freeAllocationIterator->freeFlag = 255u;
        freeAllocationIterator->occupiedBytes = allocationSize;
        showLogForAllocation(*freeAllocationIterator);
        return freeAllocationIterator->address;
    }

    freeAllocationIterator = std::find_if(allocations.begin(),allocations.end(),[size = allocationSize](const auto &allocation){
        return (allocation.allocatedBytes - allocation.occupiedBytes) >= size;
    });

    if(freeAllocationIterator != allocations.end())
    {
        Allocation allocation{};
        allocation.freeFlag = 0u;
        allocation.allocatedBytes = freeAllocationIterator->allocatedBytes - freeAllocationIterator->occupiedBytes;
        allocation.occupiedBytes  = allocationSize;
        allocation.address = (vptr) (((u64)freeAllocationIterator->allocatedBytes) + (freeAllocationIterator->occupiedBytes));

        freeAllocationIterator->allocatedBytes = freeAllocationIterator->occupiedBytes;

        showLogForAllocation(allocation);

        allocations.push_back(allocation);

        return allocation.address;
    }
    if(lastAddress >= maxAddress)
    {
        SDL_Log("Failed to allocate memory for object.\n");
        return nullptr;
    }
    Allocation allocation{};
    allocation.freeFlag  = 0u;
    allocation.allocatedBytes  = allocationSize;
    allocation.occupiedBytes = allocationSize;
    allocation.address = lastAddress;

    showLogForAllocation(allocation);

    allocations.push_back(allocation);

    lastAddress = (vptr)(((u64)lastAddress) + allocationSize);
    return allocation.address;
}

inline void core::mem::MemoryPool::showLogForAllocation(const MemoryPool::Allocation &allocation)
{
    auto freeMemory = (((u64)maxAddress) - (u64)lastAddress);
    SDL_Log("Allocated memory from address : %p.\nOccupied Bytes: %lu.\nAllocated memory for object: %lu.\nPool size : %lu.\nPool memory begin address : %p.\nAllocation objects : %zu.\nFree memory in pool: %lu.\n" ,allocation.address,allocation.occupiedBytes,allocation.allocatedBytes,size,memory,allocations.size(),freeMemory);

}

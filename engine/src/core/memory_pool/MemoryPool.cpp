//
// Created by cx9ps3 on 09.05.2023.
//

#include "MemoryPool.h"
#include <SDL3/SDL.h>
#include <malloc.h>
#include <algorithm>


/**
 * @class MemoryPool
 * @brief This class represents a memory pool with a specified size.
 */

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
    for(auto &allocation : allocations)
    {
        if(allocation.freeFlag == 1u && allocation.allocatedBytes >= size)
        {
            allocation.freeFlag = 255u;
            allocation.occupiedBytes = allocationSize;
            showLogForAllocation(allocation);
            return allocation.address;
        }
        if((allocation.allocatedBytes - allocation.occupiedBytes) >= size)
        {
            Allocation newAllocation{};
            newAllocation.freeFlag = 0u;
            newAllocation.allocatedBytes = allocation.allocatedBytes - allocation.occupiedBytes;
            newAllocation.occupiedBytes  = allocationSize;
            newAllocation.address = (vptr) (((u64)allocation.allocatedBytes) + (allocation.occupiedBytes));

            allocation.allocatedBytes = allocation.occupiedBytes;

            showLogForAllocation(newAllocation);


            allocations.push_back(newAllocation);

            return newAllocation.address;
        }
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

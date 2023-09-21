//
// Created by cx9ps3 on 09.05.2023.
//

#include "MemoryPool.hpp"
#include <SDL3/SDL.h>
#include <algorithm>
#include <malloc.h>

hexen::engine::core::memory::MemoryPool::MemoryPool(u64 size) : size(size)
{
	memory = malloc(size);
	lastAddress = memory;
	maxAddress = (vptr) (((u64) memory) + (size));
	SDL_Log("Allocated memory in pool : %llu bytes.\nMemory address : %p.\n", size, memory);
}

void hexen::engine::core::memory::MemoryPool::free(vptr address) noexcept
{
	auto iterator = std::find_if(allocations.begin(), allocations.end(), [address = address](const auto &allocation)
			{ return allocation.address == address; });
	if (iterator != allocations.end())
	{
		SDL_Log("Freed allocation from address: %p\n.Returned memory to pool : %llu.\n", address, iterator->occupiedBytes);
		iterator->freeFlag = 1u;
		iterator->occupiedBytes = 0;
	}
}

hexen::engine::core::memory::MemoryPool::~MemoryPool()
{
	free(memory);
	SDL_Log("Freed memory from pool  address : %p.Size of freed memory: %llu.\n", memory, size);
}

hexen::engine::core::vptr hexen::engine::core::memory::MemoryPool::allocate(u64 allocationSize)
{
	for (auto &allocation : allocations)
	{
		if (allocation.freeFlag == 1u && allocation.allocatedBytes >= size)
		{
			allocation.freeFlag = 255u;
			allocation.occupiedBytes = allocationSize;
			showLogForAllocation(allocation);
			return allocation.address;
		}
		if ((allocation.allocatedBytes - allocation.occupiedBytes) >= size)
		{
			Allocation newAllocation {};
			newAllocation.freeFlag = 0u;
			newAllocation.allocatedBytes = allocation.allocatedBytes - allocation.occupiedBytes;
			newAllocation.occupiedBytes = allocationSize;
			newAllocation.address = (vptr) (((u64) allocation.allocatedBytes) + (allocation.occupiedBytes));

			allocation.allocatedBytes = allocation.occupiedBytes;

			showLogForAllocation(newAllocation);


			allocations.push_back(newAllocation);

			return newAllocation.address;
		}
	}

	if (lastAddress >= maxAddress)
	{
		SDL_Log("Failed to allocate memory for object.\n");
		return nullptr;
	}
	Allocation allocation {};
	allocation.freeFlag = 0u;
	allocation.allocatedBytes = allocationSize;
	allocation.occupiedBytes = allocationSize;
	allocation.address = lastAddress;

	showLogForAllocation(allocation);

	allocations.push_back(allocation);

	lastAddress = (vptr) (((u64) lastAddress) + allocationSize);
	return allocation.address;
}

inline void hexen::engine::core::memory::MemoryPool::showLogForAllocation(const MemoryPool::Allocation &allocation)
{
	auto freeMemory = (((u64) maxAddress) - (u64) lastAddress);
	SDL_Log("Allocated memory from address : %p.\nOccupied Bytes: %llu.\nAllocated memory for object: %llu.\nPool size : %llu.\nPool memory begin address : %p.\nAllocation objects : %zu.\nFree memory in pool:%lluu.\n", allocation.address, allocation.occupiedBytes, allocation.allocatedBytes, size, memory, allocations.size(), freeMemory);
}

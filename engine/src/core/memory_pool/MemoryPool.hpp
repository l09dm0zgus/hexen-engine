//
// Created by cx9ps3 on 09.05.2023.
//

#pragma once

#include "../Types.hpp"
#include <vector>
namespace hexen::engine::core::memory
{
	class MemoryPool
	{
		struct Allocation
		{
			u8 freeFlag {0};
			u64 allocatedBytes {0};
			u64 occupiedBytes {0};
			vptr address {nullptr};
		};

	public:
		/**
        * @class MemoryPool
        * @brief This class represents a memory pool with a specific size.
        *
        * The MemoryPool class provides functionality to create a memory pool object with a given size.
        * It allows allocation and deallocation of memory within the pool.
        */

		explicit MemoryPool(u64 size);

		/**
        * @class MemoryPool
        * @brief Represents a memory pool that dynamically allocates and releases memory.
        *
        * The MemoryPool class provides a simple implementation for managing fixed-size
        * memory chunks. It allows efficient allocation and deallocation of memory blocks.
        */

		~MemoryPool();

		/**
        * @class MemoryPool
        * @brief A class representing a memory pool for allocating fixed-size memory blocks.
        *
        * The MemoryPool class provides functionality to allocate fixed-size memory blocks from a pre-allocated memory pool.
        * It manages a pool of memory blocks of the same size and allows efficient allocation and deallocation of these blocks.
        * This class is useful in scenarios where there is a need for frequent allocation and deallocation of fixed-size blocks.
         */

		vptr allocate(u64 size);

		/**
        * @brief Frees the memory block at the given address.
        *
        * This function is used to deallocate a previously allocated memory block by the MemoryPool.
        * It does not perform any memory cleanup or call any destructors associated with the freed memory block.
        *
        * Note that this function is noexcept, meaning it won't throw any exceptions.
        *
        * @param address The address of the memory block to be freed.
        */

		void free(vptr address) noexcept;

		MemoryPool(MemoryPool &&memoryPool) = delete;
		MemoryPool(const MemoryPool &memoryPool) = delete;

		MemoryPool &operator=(MemoryPool &&memoryPool) = delete;
		MemoryPool &operator=(const MemoryPool &memoryPool) = delete;

	private:
		/**
        * @brief Displays the log entry for a specific allocation.
        *
        * This function displays the log entry for a given allocation in the memory pool.
        *
        * @param allocation The allocation for which to display the log entry.
        */

		inline void showLogForAllocation(const Allocation &allocation);
		std::vector<Allocation> allocations;
		u64 size;
		vptr memory;
		vptr lastAddress;
		vptr maxAddress;
	};
}// namespace hexen::engine::core::memory

//
// Created by cx9ps3 on 09.05.2023.
//

#pragma once

#include "../Types.hpp"
#include <vector>
namespace hexen::engine::core::memory
{
	/**
     * @class MemoryPool
     * @brief This class represents a memory pool with a specific size.
     *
     * The MemoryPool class provides functionality to create a memory pool object with a given size.
     * It allows allocation and deallocation of memory within the pool.
     */

	class MemoryPool
	{
		/**
 		* @struct Allocation
 		*
 		* @brief A structure used to manage memory allocation.
	 	*
 		* This structure maintains important information about a specific block of memory.
 		*/

		struct Allocation
		{
			/**
     		* @brief Flag indicating whether this allocation block is free or not.
     		*
     		* A value of 0 indicates that the block is free, i.e., it is currently being used.
     		* Any other value indicates that the block is free.
     		*/

			u8 freeFlag {0};

			/**
     		* @brief Represents the total number of bytes allocated for this block.
     		*
     		* This value includes both used and unused bytes.
     		*/

			u64 allocatedBytes {0};

			/**
     		* @brief Represents the total number of occupied bytes in the allocation block.
     		*
     		* This should not be greater than allocatedBytes.
     		*/

			u64 occupiedBytes {0};

			/**
     		* @brief The memory address for this allocation block.
     		*
     		* A null value indicates that no memory has been allocated for this block.
     		*/

			vptr address {nullptr};
		};

	public:

		/**
 		* @brief Constructor for the MemoryPool class.
 		*
 		* Creates a MemoryPool object with the specified size. The object allocates a block
 		* of memory of this size via malloc in its constructor to use it for memory pool.
 		* After allocating the memory, it assigns the base memory address to the lastAddress
 		* member and the address of the last byte in the allocated block to maxAddress member.
 		* Finally, it logs about the allocated memory size and the base address of the memory block.
 		*
 		* Note: The allocated block of memory needs to be deallocated in the destructor.
 		*
 		* @param size Size in bytes of the memory pool to be created.
 		*/

		explicit MemoryPool(u64 size);

		/**
		* @brief Destructor of MemoryPool class
		*
		* The destructor is responsible for freeing the memory allocated by the MemoryPool.
		* An SDL_Log message is logged mentioning the address of the freed memory and its size.
		*/

		~MemoryPool();

		/**
 		* @brief Allocates memory from the memory pool.
 		*
 		* This function iterates over all the allocations in the pool to find an adequate allocation that can fit the requested size.
 		* If such allocation is found, the function changes its flags, assigns the allocation size to the occupiedBytes and displays the allocation log.
 		* If an allocation has enough free space left, a new allocation is created within it and the allocatedBytes of the original allocation is updated.
 		* The function will stop if the memory pool limit (maxAddress) is reached and display an error message.
 		* At the end, if no adequate allocation was found, a new one is created at the lastAddress, and the occupiedBytes and allocatedBytes are set to the requested allocation size.
 		*
 		* @param allocationSize The size of the memory to be allocated.
 		* @return The address of the allocated memory, or nullptr if the allocation failed (i.e., the memory pool was full).
 		*
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

		/**
 		*
 		* @brief Deleted move constructor.
 		*
 		* Deleting the move constructor prohibits the moving of objects.
 		*
	 	* @param memoryPool The MemoryPool to move. This parameter is not used as the method is deleted.
 		*/

		MemoryPool(MemoryPool &&memoryPool) = delete;

		/**
 		*
 		* @brief Deleted copy constructor.
 		*
 		* Deleting the copy constructor prohibits the copying of objects.
 		*
 		* @param memoryPool The MemoryPool to copy. This parameter is not used as the method is deleted.
 		*/

		MemoryPool(const MemoryPool &memoryPool) = delete;

		/**
 		*
	 	* @brief Deleted move assignment operator.
 		*
 		* Deleting the move assignment operator prohibits the moving of objects.
 		*
 		* @param memoryPool The MemoryPool to move. This parameter is not used as the method is deleted.
 		* @return None. This is a deleted method.
	 	*/

		MemoryPool &operator=(MemoryPool &&memoryPool) = delete;

		/**
		*
 		* @brief Deleted copy assignment operator.
 		*
 		* Deleting the copy assignment operator prohibits the copying of objects.
 		*
 		* @param memoryPool The MemoryPool to copy. This parameter is not used as the method is deleted.
 		* @return None. This is a deleted method.
 		*/

		MemoryPool &operator=(const MemoryPool &memoryPool) = delete;

	private:
		/**
        * @brief Displays the log entry for a specific allocation.
        *
        * This function displays the log entry for a given allocation in the memory pool.
        *
        * @param allocation The allocation for which to display the log entry.
        */

		HEXEN_INLINE void showLogForAllocation(const Allocation &allocation);

		/**
 		* @var std::vector<Allocation> allocations
 		* @brief It holds the list of memory allocations made.
 		*/

		std::vector<Allocation> allocations;

		/**
		* @var u64 size
 		* @brief It contains the size of the memory allocation.
 		* It represents the total amount of memory allocated.
 		*/

		u64 size;

		/**
 		* @var vptr memory
 		* @brief It contains the starting address of the allocated memory.
 		*/

		vptr memory;

		/**
 		* @var vptr lastAddress
 		* @brief This variable contains the last address of the allocated memory block.
 		*/

		vptr lastAddress;

		/**
 		* @var vptr maxAddress
 		* @brief It contains the maximum available address for allocation in memory.
 		*/

		vptr maxAddress;
	};
}// namespace hexen::engine::core::memory

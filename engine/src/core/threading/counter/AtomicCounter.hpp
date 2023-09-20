
#pragma once

#include "BaseCounter.hpp"

namespace hexen::engine::core::threading
{

	/**
 	* @class FullAtomicCounter
	* @brief This class manages atomic operations on an integer with thread safety.
 	*
 	* @details It is derived from the BaseCounter class. It disallows copy and move semantics. It contains methods to atomically load, store, add, subtract,
 	* and compare and exchange the value of the counter, with user specified memory order.
 	*/

	class FullAtomicCounter : public BaseCounter
	{

	public:

		/**
		* @brief Construct a new Full Atomic Counter object.
		* @param taskScheduler A pointer to the TaskScheduler object.
		* @param initialValue The initial value of the counter.
		* @param fiberSlots The number of fiber slots. Default is NUMBER_OF_WAITING_FIBER_SLOTS.
		*/

		explicit FullAtomicCounter(TaskScheduler *taskScheduler, u32 const initialValue = 0, u32 const fiberSlots = NUMBER_OF_WAITING_FIBER_SLOTS) : BaseCounter(taskScheduler, initialValue, fiberSlots) {}

		///@breif Deleted functions to prevent copy and move semantics.
		FullAtomicCounter(FullAtomicCounter const &) = delete;
		FullAtomicCounter(FullAtomicCounter &&) noexcept = delete;
		FullAtomicCounter &operator=(FullAtomicCounter const &) = delete;
		FullAtomicCounter &operator=(FullAtomicCounter &&) noexcept = delete;

		///@brief Default destructor.
		~FullAtomicCounter() = default;

	public:

		/**
		* @brief Load the value of the counter atomically.
		* @param memoryOrder The memory order for the atomic operation. Default is std::memory_order_seq_cst.
		* @return The loaded value of the counter.
		*/

		u32 load(std::memory_order const memoryOrder = std::memory_order_seq_cst)
		{
			lock.fetch_add(1U, std::memory_order_seq_cst);

			auto result = value.load(memoryOrder);

			lock.fetch_sub(1U, std::memory_order_seq_cst);
			return result;
		}

		/**
		* @brief Store a value to the counter atomically.
		* @param x The value to be stored.
		* @param memoryOrder The memory order for the atomic operation. Default is std::memory_order_seq_cst.
		*/

		void store(u32 const x, std::memory_order const memoryOrder = std::memory_order_seq_cst)
		{
			lock.fetch_add(1U, std::memory_order_seq_cst);

			value.store(x, memoryOrder);
			checkWaitingFibers(x);

			lock.fetch_sub(1U, std::memory_order_seq_cst);
		}

		/**
		* @brief Atomically adds a value to the counter and returns the previous value.
		* @param x The value to be added.
		* @param memoryOrder The memory order for the atomic operation. Default is std::memory_order_seq_cst.
		* @return The previous value of the counter before the addition.
		*/

		u32 fetchAdd(u32 const x, std::memory_order const memoryOrder = std::memory_order_seq_cst)
		{
			lock.fetch_add(1U, std::memory_order_seq_cst);

			const auto previous = value.fetch_add(x, memoryOrder);
			checkWaitingFibers(previous + x);

			lock.fetch_sub(1U, std::memory_order_seq_cst);
			return previous;
		}

		/**
		* @brief Atomically subtracts a value from the counter and returns the previous value.
		* @param x The value to be subtracted.
		* @param memoryOrder The memory order for the atomic operation. Default is std::memory_order_seq_cst.
		* @return The previous value of the counter before the subtraction.
		*/

		u32 fetchSub(u32 const x, std::memory_order const memoryOrder = std::memory_order_seq_cst)
		{
			lock.fetch_add(1U, std::memory_order_seq_cst);

			const auto previous = value.fetch_sub(x, memoryOrder);
			checkWaitingFibers(previous - x);

			lock.fetch_sub(1U, std::memory_order_seq_cst);
			return previous;
		}

		/**
		* @brief Atomically compares the counter to an expected value and, if they are the same, replaces the counter with a new value.
		* @param expectedValue The expected value to be compared with the counter.
		* @param newValue The new value to replace the counter with if the comparison is successful.
		* @param memoryOrder The memory order for the atomic operation. Default is std::memory_order_seq_cst.
		* @return True if the comparison was successful and the counter was replaced, otherwise false.
		*/

		bool compareExchange(u32 expectedValue, u32 const newValue, std::memory_order const memoryOrder = std::memory_order_seq_cst)
		{
			lock.fetch_add(1U, std::memory_order_seq_cst);

			auto const success = value.compare_exchange_strong(expectedValue, newValue, memoryOrder);
			if (success)
			{
				checkWaitingFibers(newValue);
			}

			lock.fetch_sub(1U, std::memory_order_seq_cst);
			return success;
		}
	};

	/**
 	* @class AtomicFlag
 	* @brief A class representing an atomic flag for safe multi-threaded access.
 	* @details AtomicFlag inherits from the BaseCounter class and cannot be copied or moved.
 	* The class overrides the assignment operators to prevent copying and moving.
 	*
 	*/

	class AtomicFlag : public BaseCounter
	{
	public:

		/**
	     * @brief Explicit constructor for AtomicFlag.
	     */

		explicit AtomicFlag(TaskScheduler *taskScheduler, u32 const initialValue = 0, u32 const fiberSlots = NUMBER_OF_WAITING_FIBER_SLOTS) : BaseCounter(taskScheduler, initialValue, fiberSlots) {}

		/**
	     * @brief Deleted copy constructor.
	     */

		AtomicFlag(AtomicFlag const &) = delete;

		/**
	     * @brief Deleted move constructor.
	     */

		AtomicFlag(AtomicFlag &&) noexcept = delete;

		/**
	     * @brief Deleted copy assignment operator.
	     */

		AtomicFlag &operator=(AtomicFlag const &) = delete;

		/**
	     * @brief Deleted move assignment operator.
	     */

		AtomicFlag &operator=(AtomicFlag &&) noexcept = delete;

		/**
	     * @brief Default destructor.
	     */

		~AtomicFlag() = default;

	public:

		/**
	     * @brief Sets the value of the atomic flag to 1 and returns whether the previous value was 0.
	     *
	     * @return bool
	     */

		bool set(std::memory_order const memoryOrder = std::memory_order_seq_cst)
		{
			return value.exchange(1U, memoryOrder) == 0;
		}

		/**
	     * @brief Clears the value of the atomic flag to 0 and returns whether the previous value was 1.
	     *
	     * @return bool
	     */

		bool clear(std::memory_order const memoryOrder = std::memory_order_seq_cst)
		{
			lock.fetch_add(1U, std::memory_order_seq_cst);

			const auto success = value.exchange(0U, memoryOrder) == 1;
			if (!success)
			{
				lock.fetch_sub(1U, std::memory_order_seq_cst);
				return false;
			}
			checkWaitingFibers(0U);

			lock.fetch_sub(1U, std::memory_order_seq_cst);
			return true;
		}
	};
}// namespace hexen::engine::core::threading

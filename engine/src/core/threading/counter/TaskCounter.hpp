#pragma once

#include "BaseCounter.hpp"

namespace hexen::engine::core::threading
{
	class TaskScheduler;

	/**
 	* @class TaskCounter
 	* @brief This class maintains a counter that correlates with certain tasks.
 	*
 	* TaskCounter is a type of BaseCounter that provides functionality to keep track of the count
 	* of certain tasks. It is not copyable or movable, but it can be created and manipulated.
 	*
 	* @extends BaseCounter
 	*/

	class TaskCounter : public BaseCounter
	{

	public:

		/**
     	* @brief Constructs a new TaskCounter.
     	*
     	* @param taskScheduler Pointer to a task scheduler.
     	* @param initialValue Initial counter value. Default is 0.
     	* @param fiberSlots The number of fiber slots. Default is NUMBER_OF_WAITING_FIBER_SLOTS.
     	*/

		explicit TaskCounter(TaskScheduler *taskScheduler, u32 const initialValue = 0, u32 const fiberSlots = NUMBER_OF_WAITING_FIBER_SLOTS) : BaseCounter(taskScheduler, initialValue, fiberSlots) {}

		///@brief Deleted copy constructor.
		TaskCounter(TaskCounter const &) = delete;

		/// @brief Deleted move constructor.
		TaskCounter(TaskCounter &&) noexcept = delete;

		/// @brief Deleted copy assignment constructor.
		TaskCounter &operator=(TaskCounter const &) = delete;

		/// @brief Deleted move assignment constructor.
		TaskCounter &operator=(TaskCounter &&) noexcept = delete;

		/**
 		* @brief Default destructor for the TaskCounter class
 		*/

		~TaskCounter() = default;

	public:

		/**
     	* @brief Constructs a new TaskCounter.
     	*
     	* @param taskScheduler Pointer to a task scheduler.
     	* @param initialValue Initial counter value. Default is 0.
     	*@param fiberSlots The number of fiber slots. Default is NUMBER_OF_WAITING_FIBER_SLOTS.
     	*/

		void add(core::u32 const x)
		{
			value.fetch_add(x, std::memory_order_seq_cst);
		}

		/**
     	* @brief Decrements the counter value by 1.
     	*
     	* When the new counter value is zero, it checks for waiting fibers.
     	*/

		void decrement()
		{
			lock.fetch_add(1U, std::memory_order_seq_cst);

			const auto previous = value.fetch_sub(1U, std::memory_order_seq_cst);
			const auto newValue = previous - 1;

			// TaskCounters are only allowed to wait on 0, so we only need to check when newValue would be zero
			if (newValue == 0)
			{
				checkWaitingFibers(newValue);
			}

			lock.fetch_sub(1U, std::memory_order_seq_cst);
		}
	};
}// namespace hexen::engine::core::threading

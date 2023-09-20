#pragma once

#include "../../Types.hpp"
#include <atomic>
#include <limits>

namespace hexen::engine::core::threading
{

	class TaskScheduler;

	/**
 	* @class BaseCounter
 	* @brief A base counter class used in task scheduling.
 	*
 	* This class holds the methods and variables necessary to manage task counters.
 	*/

	class BaseCounter
	{
	public:
		/** Maximum number of fiber slots waiting. */
		static constexpr u32 NUMBER_OF_WAITING_FIBER_SLOTS = 4;

		/**
     	* @brief Constructor, initializes the base counter with initial value and fiber slots.
     	* @param taskScheduler Pointer to an external TaskScheduler object.
     	* @param initialValue Initial value for the counter.
     	* @param fiberSlots Number of waiting fiber slots.
     	*/

		explicit BaseCounter(TaskScheduler *taskScheduler, u32 initialValue = 0, u32 fiberSlots = NUMBER_OF_WAITING_FIBER_SLOTS);

		/**
     	* @brief Deleted copy constructor to prevent copying
     	*/

		BaseCounter(BaseCounter const &) = delete;

		/**
     	* @brief Deleted move constructor to prevent moving
     	*/

		BaseCounter(BaseCounter &&) noexcept = delete;

		/**
     	* @brief Deleted assignment operator to prevent assignment
     	*/

		BaseCounter &operator=(BaseCounter const &) = delete;

		/**
     	* @brief Deleted move assignment operator to prevent move assignment
     	*/

		BaseCounter &operator=(BaseCounter &&) noexcept = delete;

		/**
     	* @brief Destructor
     	*/

		~BaseCounter();

	protected:
		/** Pointer to a task scheduler object */
		TaskScheduler *taskScheduler;

		/** Atomically-modifiable unsigned 32-bit integer */
		std::atomic<u32> value;

		/** Lock to be used for value variable */
		std::atomic<u32> lock;

		/** Array to store free slots */
		std::atomic<bool> *freeSlots;

		/** Memory to store free slots */
		std::atomic<bool> freeSlotsStorage[NUMBER_OF_WAITING_FIBER_SLOTS];

		/**
     	* @struct WaitingFiberBundle
     	* @brief Struct to hold the details of waiting fibers.
     	*/

		struct WaitingFiberBundle
		{
			/**
         	* @brief Constructor
         	*/

			WaitingFiberBundle();

			/** Boolean that shows if this bundle is in use */
			std::atomic<bool> inUse;

			/** Pointer to the fiber bundle */
			vptr fiberBundle {nullptr};

			/** 32-bit unsigned integer target value */
			u32 targetValue {0};

			/** Index of the pinned thread */
			u32 pinnedThreadIndex;
		};

		/** Pointer to a WaitingFiberBundle object */
		WaitingFiberBundle *waitingFibers;

		/** Memory to store the waiting fiber bundles */
		WaitingFiberBundle waitingFibersStorage[NUMBER_OF_WAITING_FIBER_SLOTS];

		/** Number of fiber slots */
		u32 fiberSlots;

		/** Friend class allows access to protected and private members of BaseCounter */
		friend class TaskScheduler;

	protected:
		/**
     	* @brief Adds a fiber to the waiting list
     	* @param fiberBundle The fiber to be added.
     	* @param targetValue The target value of the counter for the fiber to be triggered.
     	* @param pinnedThreadIndex The index of the pinned thread. The default is the maximum 32-bit unsigned integer.
     	* @return Returns true if the operation is successful, false otherwise.
     	*/

		bool addFiberToWaitingList(vptr fiberBundle, u32 targetValue, u32 pinnedThreadIndex = std::numeric_limits<u32>::max());

		/**
     	* @brief Check the waiting fibers for any that have reached their target value
     	* @param value The current counter value
     	*/

		void checkWaitingFibers(u32 value);
	};
}// namespace hexen::engine::core::threading

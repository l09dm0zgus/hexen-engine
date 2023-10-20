
#pragma once

#include "../../Types.hpp"
#include "Config.hpp"

#include <atomic>
#include <memory>
#include <vector>

namespace hexen::engine::core::threading
{
	/**
	* @class WaitFreeQueue
	* @brief A wait-free concurrent queue.
	*
	* @tparam T The type of the elements in the queue.
	*/

	template<typename T>
	class WaitFreeQueue
	{
	private:
		constexpr static size_t startingCircularArraySize = 32;

	public:
		/**
    	* @brief Constructor.
    	*
    	* Initializes an empty queue.
    	*/

		WaitFreeQueue() : top(1), bottom(1), array(new CircularArray(startingCircularArraySize)) {}

		/**
     	* @brief Deleted copy constructor to ensure that instances of WaitFreeQueue can't be copied.
     	*
     	* @param other Another instance of WaitFreeQueue.
     	*/

		WaitFreeQueue(WaitFreeQueue const &) = delete;

		/**
     	* @brief Deleted move constructor to provide strong exception guarantee (noexcept).
     	* Instances of WaitFreeQueue can't be moved.
     	*
     	* @param other Another instance of WaitFreeQueue.
     	*/

		WaitFreeQueue(WaitFreeQueue &&) noexcept = delete;

		/**
     	* @brief Deleted copy assignment operator to ensure that instances of WaitFreeQueue can't be copied.
     	*
     	* @param other Another instance of WaitFreeQueue.
     	* @return reference to the instance.
     	*/

		WaitFreeQueue &operator=(WaitFreeQueue const &) = delete;

		/**
     	* @brief Deleted move assignment operator to provide strong exception guarantee (noexcept).
     	* Instances of WaitFreeQueue can't be moved.
     	*
     	* @param other Another instance of WaitFreeQueue.
     	* @return reference to the instance.
     	*/

		WaitFreeQueue &operator=(WaitFreeQueue &&) noexcept = delete;

		/**
     	* @brief Destructor that releases the memory allocated by the waiter-free queue.
     	*/

		~WaitFreeQueue()
		{
			delete array.load(std::memory_order_relaxed);
		}

	private:
		/**
 		* @class CircularArray
 		* @brief A class that represents a circular array.
 		*
 		* This class provides methods for managing a circular array. It allows
 		* growing the array which returns a new circular array object and keeps
 		* a linked list of all previous arrays. This is done because other threads
 		* could still be accessing elements from the smaller arrays.
 		*/

		class CircularArray
		{
		public:
			/**
     		* @brief Constructor for CircularArray class.
     		* @param n The initial size of the circular array. It must be a power of 2.
     		*/

			explicit CircularArray(size_t const n) : items(n)
			{
				HEXEN_ADD_TO_PROFILE();
				HEXEN_ASSERT(!(n == 0) && !(n & (n - 1)), "n must be a power of 2");
			}

		private:
			std::vector<T> items;					///@brief A vector storing the circular array elements
			std::unique_ptr<CircularArray> previous;///@brief A unique pointer to the previous CircularArray object

		public:
			/**
     		* @brief Get the size of the circular array.
     		* @return The size of the circular array.
     		*/

			[[nodiscard]] size_t size() const
			{
				HEXEN_ADD_TO_PROFILE();
				return items.size();
			}

			/**
     		* @brief Get the element at the given index.
     		* @param index The index from where to get the element.
     		* @return The element at the given index.
     		*/

			T get(size_t const index)
			{
				HEXEN_ADD_TO_PROFILE();
				return items[index & (size() - 1)];
			}

			/**
     		* @brief Store an element at the given index in the circular array.
     		* @param index The index where to put the element.
     		* @param x The element to put in the circular array.
     		*/

			void put(size_t const index, T x)
			{
				HEXEN_ADD_TO_PROFILE();
				items[index & (size() - 1)] = x;
			}

			/**
     		* @brief Grow the circular array and move elements from the current array to the new one.
     		*
     		* Growing the array returns a new circular_array object and keeps a
     		* linked list of all previous arrays. This is done because other threads
     		* could still be accessing elements from the smaller arrays.
     		*
     		* @param top The start index.
     		* @param bottom The end index.
     		* @return The new, larger circular array.
     		*/

			CircularArray *grow(size_t const top, size_t const bottom)
			{
				HEXEN_ADD_TO_PROFILE();
				auto *const newArray = new CircularArray(size() * 2);
				newArray->previous.reset(this);
				for (size_t i = top; i != bottom; i++)
				{
					newArray->put(i, get(i));
				}
				return newArray;
			}
		};

#pragma warning(push)
#pragma warning(disable : 4324)// MSVC warning C4324: structure was padded due to alignment specifier
		alignas(cacheLineSize) std::atomic<core::u64> top;
		alignas(cacheLineSize) std::atomic<core::u64> bottom;
		alignas(cacheLineSize) std::atomic<CircularArray *> array;
#pragma warning(pop)

	public:
		/**
 		* @brief Inserts a value at the bottom of the queue.
 		*
 		* @param value The value to be inserted into the queue.
 		*/

		void push(T value)
		{
			HEXEN_ADD_TO_PROFILE();
			auto b = bottom.load(std::memory_order_relaxed);
			auto t = top.load(std::memory_order_acquire);
			auto *a = this->array.load(std::memory_order_relaxed);

			if (b - t > a->size() - 1)
			{
				/* Full queue. */
				a = a->grow(t, b);
				array.store(a, std::memory_order_release);
			}
			a->put(b, value);

			std::atomic_thread_fence(std::memory_order_release);

			bottom.store(b + 1, std::memory_order_relaxed);
		}

		/**
 		* @brief Removes a value from the bottom of the queue
 		*
 		* This function will return false and not alter the value of 'value' if the queue is empty.
 		*
 		* @param value A pointer where the removed value will be stored.
 		* @return true if a value was successfully removed, false otherwise.
 		*/

		bool pop(T *value)
		{
			HEXEN_ADD_TO_PROFILE();
			auto b = bottom.load(std::memory_order_relaxed) - 1;
			auto *const a = array.load(std::memory_order_relaxed);
			bottom.store(b, std::memory_order_relaxed);

			std::atomic_thread_fence(std::memory_order_seq_cst);

			auto t = top.load(std::memory_order_relaxed);
			bool result = true;
			if (t <= b)
			{
				/* Non-empty queue. */
				*value = a->get(b);
				if (t == b)
				{
					/* Single last element in queue. */
					if (!std::atomic_compare_exchange_strong_explicit(&top, &t, t + 1, std::memory_order_seq_cst, std::memory_order_relaxed))
					{
						/* Failed race. */
						result = false;
					}
					bottom.store(b + 1, std::memory_order_relaxed);
				}
			}
			else
			{
				/* Empty queue. */
				result = false;
				bottom.store(b + 1, std::memory_order_relaxed);
			}

			return result;
		}

		/**
 		* @brief Removes a value from the top of the queue
 		*
 		* This function will return false and not alter the value of 'value' if the queue is empty.
 		*
 		* 'steal' implies that the value being removed comes from the more frequently accessed top side of the queue,
 		* in a setup where one thread primarily uses 'push' and 'pop' (the "bottom" of the queue) and another thread primarily
 		* uses 'steal' (the "top" of the queue). This may be useful in a work-stealing queue scenario.
 		*
 		* @param value A pointer where the stolen value will be stored.
 		* @return true if a value was successfully removed, false otherwise.
 		*/

		bool steal(T *const value)
		{
			HEXEN_ADD_TO_PROFILE();
			auto t = top.load(std::memory_order_acquire);

			std::atomic_thread_fence(std::memory_order_seq_cst);

			auto const b = bottom.load(std::memory_order_acquire);
			if (t < b)
			{
				/* Non-empty queue. */
				auto *const a = array.load(std::memory_order_consume);
				*value = a->get(t);
				return std::atomic_compare_exchange_strong_explicit(&top, &t, t + 1, std::memory_order_seq_cst, std::memory_order_relaxed);
			}

			return false;
		}
	};
}// namespace hexen::engine::core::threading

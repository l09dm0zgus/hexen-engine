//
// Created by cx9ps3 on 01.10.2023.
//

#pragma once
#include "../core/Types.hpp"
#include "Component.hpp"
#include <type_traits>


namespace hexen::engine::components
{
	/**
 	* @tparam T Type of the components, T is base of Component
 	* @tparam SIZE Size of the container
 	* @brief Class for storing and managing components
 	*/

	template<class T, size_t SIZE, std::enable_if_t<std::is_base_of_v<Component, T>, bool> = true>
	class ComponentContainer
	{
	private:
		T components[SIZE];		   ///< Store of the components
		core::i32 indices[SIZE] {};///< Indices of each component
		size_t back;			   ///< Number of components in the container
		friend class Iterator;
	public:
		/**
        * @brief Iterator class for iterating over the component container
        */

		class Iterator
		{
		public:
			using value_type = T;									  ///< Type of the value
			using reference = T&;									  ///< Type of the reference
			using pointer = T*;
			using iterator_category = std::random_access_iterator_tag;///< Category of the iterator

			/**
			 * @brief Construct the iterator by providing the container
			 * @param newContainer Pointer to the component container
			 */

			explicit Iterator(ComponentContainer<T, SIZE> *newContainer) : container(newContainer) {};

			/**
			 * @brief Construct the iterator by providing the container and an index
			 * @param newContainer Pointer to the component container
			 * @param index Index of the current element
			 */

			explicit Iterator(ComponentContainer<T, SIZE> *newContainer, size_t index) : container(newContainer), i(index) {};

			/**
             * @brief Dereference operator
             * @return A reference to the current component
             */

			reference operator*()
			{
				return container->components[i];
			}

			pointer operator->()
			{
				return &container->components[i];
			}

			/**
             * @brief Prefix increment operator. Advances the iterator to the next component
             * @return Reference to the updated iterator
             */

			Iterator &operator++()
			{
				i++;
				return *this;
			}

			/**
             * @brief Postfix increment operator. Advances the iterator to the next component
             * @return Copy of the original iterator before incrementing
             */

			Iterator operator++(int)
			{
				Iterator temp = *this;
				++i;
				return temp;
			}

			/**
             * @brief Prefix decrement operator. Moves the iterator to the previous component
             * @return Reference to the updated iterator
             */

			Iterator &operator--()
			{
				i--;
				return *this;
			}

			/**
             * @brief Postfix decrement operator. Moves the iterator to the previous component
             * @return Copy of the original iterator before decrementing
             */

			Iterator operator--(int)
			{
				Iterator temp = *this;
				--i;
				return temp;
			}

			/**
             * @brief Equality comparison operator
             * @param lhs Left operand of the comparison
             * @param rhs Right operand of the comparison
             * @return True if both iterators point to the same component, false otherwise
             */

			friend bool operator==(const Iterator &lhs, const Iterator &rhs)
			{
				return lhs.container == rhs.container && lhs.i == rhs.i;
			}

			/**
             * @brief Inequality comparison operator
             * @param lhs Left operand of the comparison
             * @param rhs Right operand of the comparison
             * @return True if the iterators point to different components, false otherwise
             */

			friend bool operator!=(const Iterator &lhs, const Iterator &rhs)
			{
				return !(lhs == rhs);
			}

		private:
			ComponentContainer<T, SIZE> *container {nullptr};///< Pointer to the component container
			size_t i {0};									 ///< Index of the current element
		};

		/**
         * @brief Construct ComponentContainer and initialize indices
         */

		ComponentContainer() : back(0)
		{
			for (size_t i = 0; i < SIZE; i++)
			{
				indices[i] = static_cast<core::i32>(i);
			}
		}

		/**
         * @brief Reserve a new component in the container
         * @return Index of the reserved component
         */

		core::i32 reserve()
		{
			return indices[back++];
		}

		/**
		 * @brief Release a component in the container specified by its handle
		 * @param handle Handle of the component
		 */

		void release(core::i32 handle)
		{
			for (size_t i = 0; i < back; i++)
			{
				if (indices[i] == handle)
				{
					back--;
					std::swap(indices[i], indices[back]);
					return;
				}
			}
		}

		/**
         * @brief Returns an iterator pointing to the first component
         * @return Iterator pointing to the first component
         */

		Iterator begin()
		{
			return Iterator(this, 0);
		}

		/**
         * @brief Returns an iterator pointing past the end of components
         * @return Iterator pointing past the end of components
         */

		Iterator end()
		{
			return Iterator(this, back);
		}

		/**
         * @brief Get the current number of components
         * @return Number of current components
         */

		[[nodiscard]] core::i32 size() const noexcept
		{
			return back;
		}

		/**
         * @brief Check whether the container is empty
         * @return True if the container is empty, false otherwise.
         */

		[[nodiscard]] bool empty() const noexcept
		{
			return size() == 0;
		}

		/**
         * @brief Access a component with specified handle
         * @param handle Handle of the component
         * @return Component with the specified handle
         */

		T& operator[](core::i32 handle)
		{
			return components[handle];
		}
	};
}// namespace hexen::engine::components

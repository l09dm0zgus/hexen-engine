//
// Created by cx9ps3 on 01.10.2023.
//

#pragma once
#include "../core/Types.hpp"
#include "../threading/TaskSystem.hpp"
#include "Component.hpp"
#include <type_traits>


namespace hexen::engine::components
{
	/**
 	* @tparam T Type of the components, T is base of Component
 	* @tparam SIZE Size of the container
 	* @brief Class for storing and managing components
 	*/

	template<class T>
	class ComponentContainerBase
	{
	private:
		std::vector<T> components;		  ///< Store of the components
		std::vector<core::i32> indices {};///< Indices of each component
		size_t back;					  ///< Number of components in the container
		friend class Iterator;

	public:
		/**
        * @brief Iterator class for iterating over the component container
        */

		class Iterator
		{
		public:
			using difference_type = std::ptrdiff_t;
			using value_type = T; ///< Type of the value
			using reference = T &;///< Type of the reference
			using pointer = T *;
			using iterator_category = std::forward_iterator_tag;///< Category of the iterator

			/**
			 * @brief Construct the iterator by providing the container
			 * @param newContainer Pointer to the component container
			 */

			explicit Iterator(ComponentContainerBase<T> *newContainer) : container(newContainer) {};

			Iterator() = default;

			/**
			 * @brief Construct the iterator by providing the container and an index
			 * @param newContainer Pointer to the component container
			 * @param index Index of the current element
			 */

			explicit Iterator(ComponentContainerBase<T> *newContainer, size_t index) : container(newContainer), i(index) {};

			/**
             * @brief Dereference operator
             * @return A reference to the current component
             */

			reference operator*()
			{
				HEXEN_ADD_TO_PROFILE();
				return container->components[i];
			}

			pointer operator->()
			{
				HEXEN_ADD_TO_PROFILE();
				return &container->components[i];
			}

			/**
             * @brief Prefix increment operator. Advances the iterator to the next component
             * @return Reference to the updated iterator
             */

			Iterator &operator++()
			{
				HEXEN_ADD_TO_PROFILE();
				i++;
				return *this;
			}

			/**
             * @brief Postfix increment operator. Advances the iterator to the next component
             * @return Copy of the original iterator before incrementing
             */

			Iterator operator++(int)
			{
				HEXEN_ADD_TO_PROFILE();
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
				HEXEN_ADD_TO_PROFILE();
				i--;
				return *this;
			}

			/**
             * @brief Postfix decrement operator. Moves the iterator to the previous component
             * @return Copy of the original iterator before decrementing
             */

			Iterator operator--(int)
			{
				HEXEN_ADD_TO_PROFILE();
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
				HEXEN_ADD_TO_PROFILE();
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
				HEXEN_ADD_TO_PROFILE();
				return !(lhs == rhs);
			}

		private:
			ComponentContainerBase<T> *container {nullptr};///< Pointer to the component container
			size_t i {0};								   ///< Index of the current element
		};

		/**
         * @brief Construct ComponentContainer and initialize indices
         */

		explicit ComponentContainerBase(core::u64 size) : back(0)
		{
			HEXEN_ADD_TO_PROFILE();
			indices.reserve(size);
			components.reserve(size);
			for (size_t i = 0; i < size; i++)
			{
				indices.push_back(static_cast<core::i32>(i));
			}
			for (size_t i = 0; i < size; i++)
			{
				components.emplace_back();
			}
		}

		/**
         * @brief Reserve a new component in the container
         * @return Index of the reserved component
         */

		core::i32 reserve()
		{
			HEXEN_ADD_TO_PROFILE();
			return indices[back++];
		}

		/**
		 * @brief Release a component in the container specified by its handle
		 * @param handle Handle of the component
		 */

		void release(core::i32 handle)
		{
			HEXEN_ADD_TO_PROFILE();
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
			HEXEN_ADD_TO_PROFILE();
			return Iterator(this, 0);
		}

		/**
         * @brief Returns an iterator pointing past the end of components
         * @return Iterator pointing past the end of components
         */

		Iterator end()
		{
			HEXEN_ADD_TO_PROFILE();
			return Iterator(this, back);
		}

		/**
         * @brief Get the current number of components
         * @return Number of current components
         */

		[[nodiscard]] core::i32 size() const noexcept
		{
			HEXEN_ADD_TO_PROFILE();
			return back;
		}

		/**
         * @brief Check whether the container is empty
         * @return True if the container is empty, false otherwise.
         */

		[[nodiscard]] bool empty() const noexcept
		{
			HEXEN_ADD_TO_PROFILE();
			return size() == 0;
		}

		/**
         * @brief Access a component with specified handle
         * @param handle Handle of the component
         * @return Component with the specified handle
         */

		T &operator[](core::i32 handle)
		{
			HEXEN_ADD_TO_PROFILE();
			return components[handle];
		}
	};

	/**
 	* @brief Abstract base class for component containers.
 	*
 	* This class defines the core interface for component containers,
 	* providing methods for managing components within a container.
 	*/

	class IComponentContainer : public core::memory::AllocatedObject
	{
	public:
		/**
     	* @brief Virtual destructor for proper polymorphism.
     	*/

		virtual ~IComponentContainer() = default;

		/**
     	* @brief Reserves a handle for a new component.
     	* @return The handle to the newly reserved component.
     	*/

		virtual core::i32 reserve() = 0;

		/**
     	* @brief Releases the component associated with the given handle.
     	* @param handle The handle of the component to release.
     	*/

		virtual void release(core::i32 handle) = 0;

		/**
     	* @brief Returns the number of components in the container.
     	* @return The number of components.
     	*/

		[[nodiscard]] virtual core::i32 size() const = 0;

		/**
     	* @brief Checks if the container is empty.
     	* @return True if the container is empty, false otherwise.
     	*/

		[[nodiscard]] virtual bool empty() const = 0;

		/**
     	* @brief Iterates over all components in the container.
     	*/

		virtual void forEach() = 0;

		/**
     	* @brief Returns the underlying base container object.
     	* @return The base container object (implementation-specific).
     	*/

		virtual std::any getBase() = 0;
	};

	/**
 	* @brief Concrete implementation of a component container for a specific component type T.
 	*
 	* This class provides a container for storing and managing components of a
 	* specific type T, implementing the IComponentContainer interface.
 	*/

	template<typename T>
	class ComponentContainer : public engine::components::IComponentContainer
	{
	private:
		/**
     	* @brief Shared pointer to the underlying component storage.
     	*/

		std::shared_ptr<engine::components::ComponentContainerBase<T>> containerBase;

		/**
     	* @brief Callback function to be invoked for each component during forEach().
     	*/

		std::function<void(T &component)> callback;

	public:
		/**
     	* @brief Constructor.
     	* @param containerSize The initial size of the container.
     	* @param newCallback The callback function to be called for each component.
     	*/

		ComponentContainer(engine::core::u64 containerSize, const std::function<void(T &component)> &newCallback) : callback(newCallback)
		{
			containerBase = engine::core::memory::make_shared<engine::components::ComponentContainerBase<T>>(containerSize);
		}

		/**
     	* @brief Default destructor.
     	*/

		~ComponentContainer() override = default;

		/**
     	* @copydoc IComponentContainer::reserve()
     	*/

		engine::core::i32 reserve() override
		{
			return containerBase->reserve();
		}

		/**
     	* @copydoc IComponentContainer::release()
     	*/

		void release(engine::core::i32 handle) override
		{
			containerBase->release(handle);
		}

		/**
     	* @copydoc IComponentContainer::size()
     	*/

		[[nodiscard]] engine::core::i32 size() const override
		{
			return containerBase->size();
		}

		/**
     	* @copydoc IComponentContainer::empty()
     	*/

		[[nodiscard]] bool empty() const override
		{
			return containerBase->empty();
		}

		/**
     	* @brief Iterates over all components and executes the callback for each using the TaskSystem.
     	*/

		void forEach() override
		{
			for (auto &component : *containerBase)
			{
				engine::threads::TaskSystem::addTask(engine::core::threading::TaskPriority::Normal, callback, component);
			}
		}

		/**
     	* @brief Returns the underlying base container object.
     	* @return The base container object as a shared pointer.
     	*/

		std::any getBase() override
		{
			return std::make_any<std::shared_ptr<engine::components::ComponentContainerBase<T>>>(containerBase);
		}
	};

#define HEXEN_REGISTER_COMPONENT(ComponentType) \
public:                                         \
	using ContainerType = hexen::engine::components::ComponentContainer<ComponentType>;

}// namespace hexen::engine::components

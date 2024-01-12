//
// Created by cx9ps3 on 28.12.2023.
//

#pragma once
#include "../../components/ComponentContainer.hpp"
#include "../threading/TaskSystem.hpp"
#include <any>
#include <tuple>
#include <typeindex>
#include <typeinfo>
#include <variant>

namespace hexen::engine::systems
{
	/**
 	* @brief A registry for managing component containers.
 	*
 	* This class provides a central point for registering, accessing, and managing
 	* component containers of various types. It acts as a bridge between components
 	* and other systems within the engine.
 	*/

	class ComponentsRegistry : public core::memory::AllocatedObject
	{
	private:
		/**
     	* @brief A map storing component containers, indexed by their type.
     	*/

		std::unordered_map<std::type_index, std::shared_ptr<components::IComponentContainer>> componentContainers;

	public:
		/**
     	* @brief Adds a new component container to the registry.
     	*
     	* @tparam Component The type of component to store in the container.
     	* @tparam size The initial size of the container.
     	* @param callback The callback function to be invoked for each component during forEach().
     	*/

		template<class Component, size_t size>
		void addComponentContainer(const std::function<void(Component &)> &callback)
		{
			componentContainers[typeid(Component)] = core::memory::make_shared<typename Component::ContainerType>(size, callback);
		}

		/**
     	* @brief Retrieves the base component container for a given component type.
     	*
     	* @tparam T The type of the component container to retrieve.
     	* @return A shared pointer to the base component container.
     	*/

		template<typename T>
		std::shared_ptr<components::ComponentContainerBase<T>> getBaseComponentContainer()
		{
			auto container = getComponentContainer<T>();
			try
			{
				auto containerBase = std::any_cast<std::shared_ptr<components::ComponentContainerBase<T>>>(container->getBase());
				return containerBase;
			}
			catch (std::bad_any_cast &e)
			{
				HEXEN_ASSERT(false, std::string("ERROR:Failed to get base component container.What:") + e.what());
			}
		}

		/**
     	* @brief Registers a new component of the specified type with the given arguments.
     	*
     	* @tparam T The type of component to register.
     	* @tparam Args The types of arguments to forward to the component's constructor.
     	* @param args The arguments to forward to the component's constructor.
     	* @return The handle of the newly registered component.
     	*/

		template<typename T, typename... Args>
		engine::core::i32 registerNewComponent(Args &&...args)
		{
			HEXEN_ADD_TO_PROFILE();
			engine::core::i32 handle {-1};
			auto container = getComponentContainer<T>();

			if (container != nullptr)
			{
				handle = container->reserve();
				auto containerBase = getBaseComponentContainer<T>();
				containerBase->operator[](handle) = T(std::forward<Args>(args)...);
			}
			return handle;
		}

		/**
     	* @brief Retrieves a component instance by its handle.
	    *
     	* @tparam T The type of component to retrieve.
     	* @param handle The handle of the component to retrieve.
     	* @return A pointer to the component instance, or nullptr if not found.
     	*/

		template<class T>
		T *getComponentInstanceByHandle(engine::core::i32 handle)
		{
			HEXEN_ADD_TO_PROFILE();
			auto container = getComponentContainer<T>();
			if (container != nullptr)
			{
				auto containerBase = getBaseComponentContainer<T>();
				return &containerBase->operator[](handle);
			}

			return nullptr;
		}

		/**
     	* @brief Releases a component by its handle.
     	*
     	* @tparam T The type of component to release.
     	* @param handle The handle of the component to release.
     	*/

		template<class T>
		void releaseComponentByHandle(engine::core::i32 handle)
		{
			HEXEN_ADD_TO_PROFILE();
			auto container = getComponentContainer<T>();
			if (container != nullptr)
			{
				container->release(handle);
			}
		}

		/**
     	* @brief Iterates over all component containers and invokes their forEach() methods.
     	*/

		void iterateAllContainers()
		{
			for (auto &[key, element] : componentContainers)
			{
				threads::TaskSystem::addTask(core::threading::TaskPriority::Normal, element.get(), &components::IComponentContainer::forEach);
			}
		}

		/**
     	* @brief Retrieves the component container for a given component type.
     	*
     	* @tparam T The type of component container to retrieve.
     	* @return A shared pointer to the component container.
     	*/

		template<class T>
		std::shared_ptr<components::IComponentContainer> getComponentContainer()
		{
			auto it = componentContainers.find(typeid(T));

			if (it == componentContainers.end())
			{
				HEXEN_ASSERT(false, "ERROR: Unknown component type!");
			}

			return it->second;
		}
	};
}// namespace hexen::engine::threads

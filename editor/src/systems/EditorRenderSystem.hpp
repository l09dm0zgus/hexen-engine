//
// Created by cx9ps3 on 13.07.2023.
//

#pragma once

#include "../components/debug_rendering/GridComponent.hpp"
#include <components/ComponentContainer.hpp>
#include <components/camera/CameraComponent.hpp>
#include <components/transform/TransformComponent.hpp>
#include <core/Types.hpp>
#include <systems/IRenderSystem.hpp>
#include "../components/debug_rendering/CheckerboardQuadComponent.hpp"

namespace hexen::editor::systems
{

	/**
 	* @class EditorRenderSystem
 	* @brief Class that manages the rendering features of the editor.
 	*
 	* This class is part of the Hexen engine subsystem. It handles the creation, retrieval,
 	* and release of components and also provides functionalities to render and
 	* update the editor display. Inherits from hexen::engine::systems::IRenderSystem.
	* @extends IRenderSystem
 	*/

	class EditorRenderSystem : public hexen::engine::systems::IRenderSystem
	{
	public:

		/**
 		* @brief Register a new component.
 		*
 		* This method is to reserve and assign a handle for the required
 		* TransformComponent type and return this handle.
 		*
 		* @tparam T Type of the component.
 		* @tparam Args Variadic template for passing additional arguments.
 		*
 		* @param args Additional arguments for registering the component.
 		*
 		* @return handle An integer handle referencing the component.
 		*                Returns -1 if the component type is not
 		*                components::TransformComponent.
	 	*/

		template<class T, class... Args>
		static engine::core::i32 registerNewComponent(Args... args)
		{
			HEXEN_ADD_TO_PROFILE();
			engine::core::i32 handle {-1};

			if constexpr (std::is_same_v<T, engine::components::TransformComponent>)
			{
				handle = transformComponents.reserve();
				transformComponents[handle] = engine::components::TransformComponent(args...);
				return handle;
			}
			else if constexpr (std::is_same_v<T, engine::components::graphics::CameraComponent>)
			{
				handle = camerasComponents.reserve();
				camerasComponents[handle] = engine::components::graphics::CameraComponent(args...);
				return handle;
			}
			else if constexpr (std::is_same_v<T, components::graphics::GridComponent>)
			{
				handle = debugGridComponentsContainer.reserve();
				debugGridComponentsContainer[handle] = components::graphics::GridComponent(args...);
				return handle;
			}
			else if constexpr (std::is_same_v<T, components::graphics::CheckerboardQuadComponent>)
			{
				handle = checkerboardQuadsComponents.reserve();
				checkerboardQuadsComponents[handle] = components::graphics::CheckerboardQuadComponent(args...);
				return handle;
			}
			else
			{
				static_assert(false, "Cannot register this component.Component container with T does not exist!");
			}
			return handle;
		}

		/**
 		* @brief Returns a pointer to a component instance by its handle.
 		*
 		* This function returns the address of a TransformComponent type using its handle.
 		*
 		* @tparam T Type of the component.
 		*
 		* @param handle An integer referencing the desired component.
 		*
 		* @return Pointer to the component of type T.
 		*         Returns nullptr if the component type is not
 		*         components::TransformComponent.
 		*/

		template<class T>
		static T *getComponentInstanceByHandle(engine::core::i32 handle)
		{
			HEXEN_ADD_TO_PROFILE();
			if constexpr (std::is_same_v<T, engine::components::TransformComponent>)
			{
				return &transformComponents[handle];
			}
			else if constexpr (std::is_same_v<T, engine::components::graphics::CameraComponent>)
			{
				return &camerasComponents[handle];
			}
			else if constexpr (std::is_same_v<T, components::graphics::GridComponent>)
			{
				return &debugGridComponentsContainer[handle];
			}
			else if constexpr (std::is_same_v<T, components::graphics::CheckerboardQuadComponent>)
			{
				return &checkerboardQuadsComponents[handle];
			}
			else
			{
				static_assert(false, "Cannot get component with T type.Component container with T does not exist!");
			}
			return nullptr;
		}

		/**
 		* @brief A template method to release a component by its handle.
 		*
 		* This method does some book-keeping and releases a component from its respective container.
 		* It supports types `TransformComponent` and `SpriteComponent`.
 		*
 		* @param handle The handle id of the component to be released.
 		*
 		* Template parameter:
 		* @tparam T The type of the component to be released.
 		*/

		template<class T>
		static void releaseComponentByHandle(engine::core::i32 handle)
		{
			HEXEN_ADD_TO_PROFILE();
			if constexpr (std::is_same_v<T, engine::components::TransformComponent>)
			{
				transformComponents.release(handle);
			}
			else if constexpr (std::is_same_v<T, engine::components::graphics::CameraComponent>)
			{
				camerasComponents.release(handle);
			}
			else if constexpr (std::is_same_v<T, components::graphics::GridComponent>)
			{
				debugGridComponentsContainer.release(handle);
			}
			else if constexpr (std::is_same_v<T, components::graphics::CheckerboardQuadComponent>)
			{
				checkerboardQuadsComponents.release(handle);
			}
			else
			{
				static_assert(false, "Cannot release component with T type.Component container with T does not exist!");
			}
		}

		/**
 		* @brief Constructs a new EditorRenderSystem object.
 		*
 		*/
		EditorRenderSystem() = default;

		/**
    	* @brief Applies linear interpolation to render the object based on the given alpha value.
    	*
    	* This function overrides the base class's render function and applies linear interpolation
    	* using the given alpha value to produce an interpolated render of the object.
    	*
    	* @param alpha The alpha value for linear interpolation (between 0 and 1).
    	*
    	* @note This function is an override function and should be called through the base class's render function.
    	* It interpolates the object's render based on the given alpha value.
    	*
    	*/

		void render(float alpha) override;

		/**
 		* @brief Sets the delta time for all the cameras.
 		*
 		* This method is part of the EditorRenderSystem of the hexen application.
 		* It sets the delta time for the main camera and all the available cameras.
 		* If the main camera pointer is null, an error message is produced.
 		*
 		* @param deltaTime The delta time value to be set.
 		*/

		void setDeltaTimeForCameras(float deltaTime);

		/**
 		* @brief This function updates the projection matrix of the camera component that matches the given window UUID.
 		*
 		* The function first tries to find a camera component in the `camerasComponents` collection where the owner's UUID matches the given window UUID.
 		* If such camera component is found, its projection matrix is updated based on the given window size.
 		*
 		* @param windowSize The size of the window. Defined by the x and y coordinates.
 		* @param windowUUID The UUID of the window. The function updates the camera component that has this UUID.
 		*/

		static void updateCameraMatricesByWindowUUID(const glm::vec2 &windowSize,const std::string& windowUUID);

	private:
		static constexpr size_t COMPONENTS_CONTAINER_SIZE = 10;

		/**
 		* @brief Stores grid components in the render system.
 		*
 		* Static container for GridComponent instances used in the EditorRenderSystem.
 		* These components provide essential information about the spatial
 		* grid structure used in the editor rendering system.
 		*/

		static engine::components::ComponentContainer<components::graphics::GridComponent, COMPONENTS_CONTAINER_SIZE> debugGridComponentsContainer;

		/**
 		* @brief Stores transform components in the render system.
 		*
 		* Static container for TransformComponent instances used in the EditorRenderSystem.
 		* The transform components represent location, rotation and scale
 		* of entities within the render system. It is crucial for accurately
 		* rendering these entities within the editor.
 		*/

		static engine::components::ComponentContainer<engine::components::TransformComponent, COMPONENTS_CONTAINER_SIZE> transformComponents;

		/**
 		* @brief Stores camera components in the render system.
 		*
 		* Static container for CameraComponent instances used in the EditorRenderSystem.
 		* These components provide essential information about the
 		* cameras used in the editor rendering system.
 		*/

		static engine::components::ComponentContainer<engine::components::graphics::CameraComponent, COMPONENTS_CONTAINER_SIZE> camerasComponents;

		/**
 		* @brief Stores checkerboards components in the render system.
 		*
 		* Static container for CheckerboardQuadComponent instances used in the EditorRenderSystem.
 		* These components provide essential information about the
 		* checkerboard pattern in background used in the editor rendering system.
 		*/

		static engine::components::ComponentContainer<editor::components::graphics::CheckerboardQuadComponent, COMPONENTS_CONTAINER_SIZE> checkerboardQuadsComponents;

		/**
 		* @brief Updates the grid matrices
 		*
 		* @details This function is a part of the EditorRenderSystem class and is utilized to update the various grid matrices, including View, Projection and Transform matrices. It requires a GridComponent object as an argument to operate. The function retrieves the main camera from the RenderSystem, and if the main camera is found, the function checks if the Grid Component and the camera have the same UUID. If they do, their view and projection matrices are set.
 		*
 		* The function also carries out an operation that finds the Camera and Transform components that have the same UUID with the Grid Component. If both components are found, the function sets the transform, view, and projection matrices of the GridComponent accordingly.
 		*
 		* @param debugGridComponent pointer to components::graphics::GridComponent object used for updating grid matrices.
 		* @return void.
 		*/

		void updateGridMatrices(components::graphics::GridComponent *debugGridComponent);

	};
}// namespace hexen::editor::systems

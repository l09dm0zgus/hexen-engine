//
// Created by cx9ps3 on 13.07.2023.
//

#pragma once
#include "../components/EditorCameraComponent.hpp"
#include "../components/debug_rendering/CheckerboardQuadComponent.hpp"
#include "../components/debug_rendering/GridComponent.hpp"
#include "../components/debug_rendering/ImageComponent.hpp"
#include "systems/base_system/IRenderSystem.hpp"
#include <components/ComponentContainer.hpp>
#include <components/transform/TransformComponent.hpp>
#include <core/Types.hpp>
#include <systems/base_system/ComponentsRegistry.hpp>

namespace hexen::editor::systems
{

	/**
 	* @class EditorRenderSystem
 	* @brief Class that manages the rendering features of the editor.
 	*
 	* This class is part of the Hexen engine subsystem. It handles the creation, retrieval,
 	* and release of components and also provides functionalities to render and
 	* update the editor display. Inherits from hexen::engine::threads::IRenderSystem.
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
		static engine::core::i32 registerNewComponent(Args&&... args)
		{
			HEXEN_ADD_TO_PROFILE();
			return componentsRegistry.registerNewComponent<T>(std::forward<Args>(args)...);
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
			return componentsRegistry.getComponentInstanceByHandle<T>(handle);
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
			componentsRegistry.releaseComponentByHandle<T>(handle);
		}

		/**
 		* @brief Constructs a new EditorRenderSystem object.
 		*
 		*/
		EditorRenderSystem();

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
 		* @brief Updates the grid matrices
 		*
 		* @details This function is a part of the EditorRenderSystem class and is utilized to update the various grid matrices, including View, Projection and Transform matrices. It requires a GridComponent object as an argument to operate. The function retrieves the main camera from the RenderSystem, and if the main camera is found, the function checks if the Grid Component and the camera have the same UUID. If they do, their view and projection matrices are set.
 		*
 		* The function also carries out an operation that finds the Camera and Transform components that have the same UUID with the Grid Component. If both components are found, the function sets the transform, view, and projection matrices of the GridComponent accordingly.
 		*
 		* @param debugGridComponent pointer to components::graphics::GridComponent object used for updating grid matrices.
 		* @return void.
 		*/

		void updateGridMatrices(components::graphics::GridComponent &debugGridComponent);

		/**
 		* @brief Updates CheckerboardQuadComponent's view, projection, and transform matrices.
 		*
 		* This function sequentially performs a parallel find_if operation on camerasComponents and transformComponents containers.
 		* The objective is to find, for the provided CheckerboardQuadComponent, the corresponding CameraComponent and TransformComponent.
 		* When it finds the corresponding CameraComponent, it sets the view and projection matrices in the CheckerboardQuadComponent from the CameraComponent.
 		* Similarly, when it finds the corresponding TransformComponent, it sets the transform matrix in the CheckerboardQuadComponent from the TransformComponent.
 		*
 		* @param checkerboardQuadComponent Pointer to CheckerboardQuadComponent to update.
 		*
 		* @note The function uses HEXEN_ADD_TO_PROFILE() for profiling.
 		* @note The function runs in parallel using std::execution::par policy in the find_if operation for increased performance.
 		*/

		void updateCheckerboardQuadsMatrices(components::graphics::CheckerboardQuadComponent& checkerboardQuadComponent);

		void updateImageMatrices(components::graphics::ImageComponent& imageComponent);

		static engine::systems::ComponentsRegistry componentsRegistry;

		std::shared_ptr<engine::components::ComponentContainerBase<components::graphics::EditorCameraComponent>> camerasComponents;
		std::shared_ptr<engine::components::ComponentContainerBase<engine::components::TransformComponent>> transformComponents;
	};
}// namespace hexen::editor::threads

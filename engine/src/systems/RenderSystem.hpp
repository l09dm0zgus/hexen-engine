//
// Created by cx9ps3 on 23.05.2023.
//

#pragma once

#include "../components/camera/CameraComponent.hpp"
//#include "../components/graphics/SpriteComponent.hpp"
//#include "../components/graphics/SpriteInstancedComponent.hpp"
#include "../components/transform/TransformComponent.hpp"
#include "../components/ComponentContainer.hpp"
#include "../core/Types.hpp"
#include "IRenderSystem.hpp"
#include <memory>
#include <vector>

namespace hexen::engine::systems
{
	/**
	 * @class RenderSystem
	 * @brief The RenderSystem class handles the rendering of graphics.
	 *
	 * The RenderSystem class manages the rendering process by creating and
	 * managing various rendering resources. It provides functions to initialize, update, and render
	 * the graphics in a given scene.
	 */
	class RenderSystem : public IRenderSystem
	{
	private:
		static constexpr size_t COMPONENTS_CONTAINER_SIZE = 1000;
	public:
		/**
 		* @brief This is the constructor for the RenderSystem class.
 		*
 		* @param sizeOfVectors This parameter represents the size of vectors to be used.
 		*/

		explicit RenderSystem(core::u32 sizeOfVectors);

		/**
         * @brief Adds a camera component to the render system.
         *
         * This function adds a camera component to the render system, allowing rendering of objects
         * from the viewpoint of the camera. The camera component is associated with a specific viewport
         * size and field of view (FOV).
         *
         * @param viewportWidth The width of the viewport in pixels.
         * @param viewportHeight The height of the viewport in pixels.
         * @param FOV The field of view (FOV) for the camera, specified in degrees.
         *            The FOV determines the extent of the scene visible through the camera.
         *            A smaller FOV provides a zoomed-in view, while a larger FOV provides a wider view.
         *
         * @details
         * This function creates and initializes a new camera component with the specified viewport
         */

		template<typename T, std::enable_if_t<std::is_base_of_v<hexen::engine::components::graphics::CameraComponent, T>, bool> = true>
		static void addCameraComponent(core::i32 viewportWidth, core::i32 viewportHeight, float FOV)
		{
			HEXEN_ADD_TO_PROFILE();
			camerasComponents.emplace_back(core::memory::make_shared<T>(viewportWidth, viewportHeight, FOV));
		}

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
		static core::i32 registerNewComponent(Args... args)
		{
			HEXEN_ADD_TO_PROFILE();
			core::i32 handle{-1};

			if constexpr (std::is_same_v<T,components::TransformComponent>)
			{
				handle = transformComponents.reserve();
				transformComponents[handle] = components::TransformComponent(args...);
				return handle;
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
		static T* getComponentInstanceByHandle(core::i32 handle)
		{
			HEXEN_ADD_TO_PROFILE();
			if constexpr (std::is_same_v<T,components::TransformComponent>)
			{
				return &transformComponents[handle];
			}
			return nullptr;
		}

		template<class T>
		static void releaseComponentByHandle(core::i32 handle)
		{
			HEXEN_ADD_TO_PROFILE();
			if constexpr (std::is_same_v<T,components::TransformComponent>)
			{
				transformComponents.release(handle);
			}
		}

		/**
        * @brief Retrieves the main camera instance from the RenderSystem.
        *
        * This function returns the main camera object managed by the RenderSystem. The main camera is responsible for rendering
        * the scene from the perspective of the viewer. It is typically used to set up the view and projection matrices,
        * control the camera position and orientation, and perform various camera-related operations.
        *
        * @note The main camera must be set before rendering the scene.
        *
        * @return The main camera instance.
        *
        */

		static std::shared_ptr<hexen::engine::components::graphics::CameraComponent> getMainCamera();

		/**
        * @brief Starts the rendering system
        *
        * This function initializes the rendering system and prepares it for rendering
        * operations. It should be called before any rendering is done.
        *
        * @par Example:
        * @code
        * sys::RenderSystem renderer;
        * renderer.start();
        * @endcode
        */

		void start() override;

		/**
        * @brief Render the scene with the given alpha value.
        *
        * This function is a member of the RenderSystem class within the sys namespace. It is responsible
        * for rendering the scene with the provided alpha value.
        *
        * @param alpha interpolated va;ue for correct rendering.
        *
        * @see sys::RenderSystem
        */

		void render(float alpha) override;

	private:
		/**
        * @brief Represents the spritesComponent of the RenderSystem in the sys namespace.
        *
        * The spritesComponent is responsible for managing the sprites of the RenderSystem.
        * It provides methods to add, remove, and update the sprites in the system.
        *
        */

		//static components::ComponentContainer<hexen::engine::components::graphics::SpriteComponent,COMPONENTS_CONTAINER_SIZE> spritesComponent;

		/**
        * @brief The instancedSpritesComponents variable stores the sprite components
        *        used for instanced rendering in the RenderSystem.
        *
        * This variable is accessed by the RenderSystem class to perform instanced
        * rendering of sprites. It should be populated with sprite components of
        * entities that require instanced rendering.
        *
        **/


		//static components::ComponentContainer<hexen::engine::components::graphics::SpriteInstancedComponent,COMPONENTS_CONTAINER_SIZE> instancedSpritesComponents;

		/**
        * @brief Represents a container for render system transform components.
        *
        * The transformComponents  represents a container that holds the transform
        * components of the render system. It is used within the sys namespace and belongs
        * to the RenderSystem subsystem.
        *
        * This container is used to store and manage the transform components associated
        * with the entities in the render system. It allows for easy access and manipulation
        * of the transform data required for rendering.
        *
        */

		static components::ComponentContainer<hexen::engine::components::TransformComponent,COMPONENTS_CONTAINER_SIZE> transformComponents;

		/**
        * @brief The camerasComponents variable is a member of the sys::RenderSystem class.
        *
        * This variable holds the camera components used by the render system. It is an
        * internal storage for managing render-related components.
        *
        * @see sys::RenderSystem
        * @see CameraComponent
        */

		static std::vector<std::shared_ptr<hexen::engine::components::graphics::CameraComponent>> camerasComponents;

		/**
        * @brief The identifier of the main camera in the Render System.
        *
        * The mainCameraId variable represents the identifier assigned to the main camera within the Render System.
        * This identifier is used to reference the main camera in various operations and settings related to rendering.
        *
        * By default, the mainCameraId is set to 0.
        *
        * It is important to note that the mainCameraId can be changed if needed. However, altering this value without
        * proper understanding of the Render System's functionality may lead to undesirable results or unexpected
        * behavior in the rendering process.
        *
        * @see sys::RenderSystem
        */

		static core::i32 mainCameraId;

		/**
        * @brief Updates the model matrix of the sprite component.
        *
        * This function calculates and updates the model matrix of the specified sprite component.
        * The model matrix is used to transform the sprite component's vertices from object-space to world-space.
        *
        * @param spriteComponent A pointer to the sprite component to update.
        */


		//void updateSpriteModelMatrix(hexen::engine::components::graphics::SpriteComponent *spriteComponent);

		/**
        * @brief Updates the view and projection matrices for rendering a sprite component.
        *
        * This function is used to update the view and projection matrices required for rendering
        * a sprite component on the screen. It takes a pointer to a sprite component as its parameter
        * and calculates the appropriate matrices based on the sprite's position, rotation, and scale.
        * The updated matrices can then be used in the rendering process.
        *
        * @param spriteComponent A pointer to the sprite component whose view and projection matrices
        *                        are to be updated.
        *
        * @see comp::rend::SpriteComponent
        */

		//void updateViewAndProjectionMatrices(hexen::engine::components::graphics::SpriteComponent *spriteComponent);


	};
}// namespace hexen::engine::systems

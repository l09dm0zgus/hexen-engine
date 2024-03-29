//
// Created by cx9ps3 on 23.05.2023.
//

#pragma once

#include "../base_system/ComponentsRegistry.hpp"
#include "../base_system/IRenderSystem.hpp"
#include "../components/graphics/SpriteComponent.hpp"
#include "../components/camera/CameraComponent.hpp"
#include "../components/transform/TransformComponent.hpp"
#include <Types.hpp>
#include <memory>
#include <vector>

namespace hexen::engine::graphics
{
	class Draw2DQuadsCommand;
}

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
		static constexpr size_t COMPONENTS_CONTAINER_SIZE = 10000;

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

		template<typename T, typename... Args>
		static engine::core::i32 registerNewComponent(Args &&...args)
		{
			HEXEN_ADD_TO_PROFILE();
			return componentsRegistry.registerNewComponent<T>(std::forward<Args>(args)...);
		}

		template<class T>
		static T *getComponentInstanceByHandle(engine::core::i32 handle)
		{
			HEXEN_ADD_TO_PROFILE();
			return componentsRegistry.getComponentInstanceByHandle<T>(handle);
		}

		template<class T>
		void releaseComponentByHandle(engine::core::i32 handle)
		{
			HEXEN_ADD_TO_PROFILE();
			return componentsRegistry.releaseComponentByHandle<T>(handle);
		}

	private:

		/**
        * @brief The camerasComponents variable is a member of the sys::RenderSystem class.
        *
        * This variable holds the camera components used by the render system. It is an
        * internal storage for managing render-related components.
        *
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
        */

		static core::i32 mainCameraId;

		/**
 		* @brief This method is used to add a SpriteComponent to the RenderSystem for rendering.
 		*
 		* @details The method searches through the transformComponents, trying to find a transform whose owner UUID
 		* matches the SpriteComponent's. If a match is found, it gets the 2D-quads command to add a new quad
 		* for this SpriteComponent using its texture and the corresponding TransformComponent's transformation matrix.
 		*
 		* @param spriteComponent SpriteComponent to add to the RenderSystem.
 		*
 		* The execution of this method is profiled using HEXEN_ADD_TO_PROFILE macro, allowing performance monitoring.
 		*
 		* @note The search of transformComponents is done in parallel using C++17's parallel algorithms for efficiency.
 		*/

		void addSpriteToRender(components::graphics::SpriteComponent &spriteComponent);

		/**
     	* @brief A function to update the view and projection matrices for the RenderSystem's main camera.
     	*
     	* This function calculates new matrices based on the current state of the main camera.
     	*
     	* @note It calls the `updateViewAndProjectionMatrices()` function from `draw2DQuadsCommand` object with two arguments:
     	* a call to `getViewMatrix()` and a call to `getProjectionMatrix()` for our `camerasComponents[mainCameraId]`.
     	*
     	* It's a member function, does not return anything and does not take any parameters.
     	*/

		void updateViewAndProjectionMatrices();

		std::shared_ptr<engine::graphics::Draw2DQuadsCommand> draw2DQuadsCommand;
		bool firstRun = true;
		static systems::ComponentsRegistry componentsRegistry;

	};
}// namespace hexen::engine::systems

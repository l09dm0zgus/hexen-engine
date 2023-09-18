//
// Created by cx9ps3 on 23.05.2023.
//

#pragma once

#include "../components/camera/CameraComponent.hpp"
#include "../components/graphics/SpriteComponent.hpp"
#include "../components/graphics/SpriteInstancedComponent.hpp"
#include "../components/transform/TransformComponent.hpp"
#include "../core/Types.hpp"
#include "IRenderSystem.hpp"
#include <memory>
#include <vector>

namespace hexen::engine::systems
{
	class RenderSystem : public IRenderSystem
	{
	public:
		/**
        * @class RenderSystem
        * @brief The RenderSystem class handles the rendering of graphics.
        *
        *  The RenderSystem class manages the rendering process by creating and
        * managing various rendering resources. It provides functions to initialize, update, and render
        * the graphics in a given scene.
        */

		explicit RenderSystem(core::u32 sizeOfVectors);

		/**
        * @brief Creates a sprite component.
        *
        * This function creates a sprite component using the provided vertex shader and fragment shader paths.
        * The vertexShaderPath parameter specifies the path to the vertex shader file, and
        * the fragmentShaderPath parameter specifies the path to the fragment shader file.
        *
        * @param vertexShaderPath The path to the vertex shader file.
        * @param fragmentShaderPath The path to the fragment shader file.
        * @return A sprite component object.
        *
        * @warning The vertexShaderPath and fragmentShaderPath parameters must be valid and accessible paths.
        *
        */


		static std::shared_ptr<hexen::engine::components::graphics::SpriteComponent> createSpriteComponent(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

		/**
        * Creates an instanced sprite with the provided vertex and fragment shader paths,
        * for the given number of instances and instances matrices.
        *
        * @param vertexShaderPath The path to the vertex shader source file.
        * @param fragmentShaderPath The path to the fragment shader source file.
        * @param numberOfInstances The number of instances to be rendered.
        * @param instancesMatrices An array of matrices representing the position and orientation
        *                         of each instance.
        * @return A handle to the created instanced sprite.
        *
        * @note The provided shader paths must be valid.
        * @note The provided number of instances should be positive.
        * @note The size of the instancesMatrices array should match the provided number of instances.
        *       Each element in the array represents the transformation matrix for an instance.
        *       The matrix should be in the column-major order.
        */

		static std::shared_ptr<hexen::engine::components::graphics::SpriteInstancedComponent> createSpriteInstancedSprite(const std::string &vertexShaderPath, const std::string &fragmentShaderPath, core::i32 numberOfInstances, glm::mat4 *instancesMatrices);

		/**
        * @brief Creates a transform component for rendering purposes.
        *
        * This function creates and returns a transform component object that can be used in rendering systems.
        * The transform component stores the position, rotation, and scale of an entity in 3D space.
        *
        * @return A pointer to the newly created transform component.
        */

		static std::shared_ptr<hexen::engine::components::TransformComponent> createTransformComponent();


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

		static std::vector<hexen::engine::components::graphics::SpriteComponent> spritesComponent;

		/**
        * @brief The instancedSpritesComponents variable stores the sprite components
        *        used for instanced rendering in the RenderSystem.
        *
        * This variable is accessed by the RenderSystem class to perform instanced
        * rendering of sprites. It should be populated with sprite components of
        * entities that require instanced rendering.
        *
        **/


		static std::vector<hexen::engine::components::graphics::SpriteInstancedComponent> instancedSpritesComponents;

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

		static std::vector<hexen::engine::components::TransformComponent> transformComponents;

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


		void updateSpriteModelMatrix(hexen::engine::components::graphics::SpriteComponent *spriteComponent);

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

		void updateViewAndProjectionMatrices(hexen::engine::components::graphics::SpriteComponent *spriteComponent);
	};
}// namespace hexen::engine::systems

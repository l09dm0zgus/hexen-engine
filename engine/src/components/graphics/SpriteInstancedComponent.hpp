//
// Created by cx9ps3 on 14.01.23.
//

#pragma once

#include "../../core/Types.hpp"
#include "SpriteComponent.hpp"
namespace hexen::engine::components::graphics
{
	/**
 	* @class SpriteInstancedComponent
 	* @brief Subclass of SpriteComponent that supports multiple instances of a sprite.
 	*
 	* This class represents a sprite component that has the functionalities for managing multiple instances.
 	* It provides an interface for drawing these instances.
 	*/

	class SpriteInstancedComponent : public SpriteComponent
	{
	public:

		SpriteInstancedComponent() = default;

		/**
     	* @brief Constructs a SpriteInstancedComponent.
     	*
     	* @param vertexShaderPath Path to the vertex shader.
     	* @param fragmentShaderPath Path to the fragment shader.
     	* @param numberOfInstances Number of sprite instances.
     	* @param instancesMatrices Pointer to the first element of a dynamically-allocated array of transformation matrices for each instance.
     	*/

		SpriteInstancedComponent(const std::string &vertexShaderPath, const std::string &fragmentShaderPath, core::i32 numberOfInstances, glm::mat4 *instancesMatrices);

		/**
     	* @brief Draws the sprite instances.
     	*
     	* This method is responsible for rendering the sprite instances.
     	* It is declared with the noexcept specifier to indicate that it doesn't throw exceptions.
     	*/

		void draw() noexcept override;

	private:
		/**
     	* @brief Buffer for storing sprite instance data.
     	*
     	* This buffer is used to store the details of each sprite instance for rendering.
     	*/

		hexen::engine::graphics::gl::GLVertexBuffer instancesBuffer;

		/**
     	* @brief The number of sprite instances.
     	*/

		core::i32 numberOfInstances {0};

		/**
     	* @brief Array of transformation matrices for each instance.
     	*
     	* Each matrix is used to apply a transformation to each instance.
     	*/

		glm::mat4 *instancesMatrices {nullptr};
	};
}// namespace hexen::engine::components::graphics

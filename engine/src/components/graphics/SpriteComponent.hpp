//
// Created by cx9ps3 on 04.01.23.
//

#pragma once

#include "RenderComponent.hpp"
#include "graphics/buffers/GL/GLElementsBuffer.hpp"
#include "graphics/buffers/GL/GLVertexArray.hpp"
#include "graphics/buffers/GL/GLVertexAttributes.hpp"
#include "graphics/buffers/GL/GLVertexBuffer.hpp"
#include "graphics/buffers/RectangleVertices.hpp"
#include "graphics/shaders/GL/GLShaderProgram.hpp"
#include "graphics/textures/GL/GLTexture2D.hpp"
#include <vector>

namespace hexen::engine::components::graphics
{
	/**
 	* @class SpriteComponent
 	* @brief A class that uses for creating and managing sprite components.
 	* @details This class is derived from the RenderComponent class,
 	*          and it implements the functionality needed for creating
 	*          and managing sprites in a graphics application.
 	*/

	class SpriteComponent : public RenderComponent
	{
	public:

		SpriteComponent() = default;

		/**
     	* @brief Constructs a new SpriteComponent object.
     	* @param vertexShaderPath Path to the vertex shader file.
     	* @param fragmentShaderPath Path to the fragment shader file.
     	*/

		SpriteComponent(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

		/**
     	* @brief Destroys the SpriteComponent object. Default destructor is used.
     	*/

		~SpriteComponent() override = default;

		/**
     	* @brief A function for drawing the sprite on the screen.
     	*/

		void draw() noexcept override;

		/**
     	* @brief Adds a texture to the sprite from an image file.
     	* @param pathToImage Path to the image file.
     	*/

		void addTexture(const std::string &pathToImage);

	private:
		//! A vector for storing the textures of the sprite.
		std::vector<std::shared_ptr<hexen::engine::graphics::gl::GLTexture2D>> textures;
		//! Object representing the vertex buffer.
		hexen::engine::graphics::gl::GLVertexBuffer VBO;
		//! Object containing the rectangle data of the vertices.
		hexen::engine::graphics::gl::RectangleVertices vertices;
		//! Object representing the elements buffer.
		hexen::engine::graphics::gl::GLElementsBuffer EBO;

	protected:
		//! Attributes of the vertex.
		hexen::engine::graphics::gl::GLVertexAttributes attributes;
		//! Object representing the vertex array.
		hexen::engine::graphics::gl::GLVertexArray VAO;
		//! Shared pointer to a shader program object.
		std::shared_ptr<hexen::engine::graphics::gl::shader::GLShaderProgram> shaderProgram {nullptr};

		/**
     	* @brief Binds the textures for the sprite.
     	* @details This function is essential for ensuring
     	*          that the correct textures are being used when drawing the sprite.
     	*/

		void bindTextures();
	};

}// namespace hexen::engine::components::graphics

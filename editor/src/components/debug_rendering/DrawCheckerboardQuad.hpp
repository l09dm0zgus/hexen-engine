//
// Created by cx9ps3 on 20.11.2023.
//

#pragma once
#include <shaders/ShaderProgram.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <graphics/buffers/VertexArray.hpp>
#include <graphics/render_commands/IRenderCommand.hpp>

namespace hexen::editor::components::graphics
{
	/**
 	* @class DrawCheckerboardQuad
 	* @brief Class responsible for drawing a checkerboard quad.
 	* @extends IRenderCommand
 	*
 	* This class takes care of the initialization and drawing of a checkerboard quad.
 	* It uses a shader program to draw the quad at the given size, and operates in
 	* a sequence of preliminary preparation, execution and finishing stages.
 	*/

	class DrawCheckerboardQuad : engine::graphics::IRenderCommand
	{
	private:
		static constexpr engine::core::u32 indicesArraySize = 6; ///< Array size of indices.
		static constexpr engine::core::u32 vertexArraySize = 20; ///< Array size of vertices.

		// Each pair of values represents the (u, v) coordinates of the texture associated with the vertex.
		std::array<float, vertexArraySize> quadVertices; ///< Array of vertex positions and texture coordinates.

		std::array<engine::core::u32, indicesArraySize> quadIndices; ///< Array of vertex indices forming the quad.

		// Shader program for rendering the quad.
		std::shared_ptr<engine::graphics::ShaderProgram> shaderProgram;

		std::shared_ptr<engine::graphics::VertexBuffer> vertexBuffer; ///< Buffer for storing vertices.
		std::shared_ptr<engine::graphics::VertexArray> vertexArray; ///< Array of vertex buffers.
		std::shared_ptr<engine::graphics::ElementsBuffer> elementsBuffer; ///< Buffer for storing indices.

		engine::core::i32 size; ///< Size of the checkerboard quad.
	public:

		/**
 		* @brief Constructor for the DrawCheckerboardQuad class.
 		*
 		* Initializes the DrawCheckerboardQuad object with given shader assets and size.
 		* It also sets the layout of the vertex buffer and adds it to the vertex array
 		* together with the elements buffer.
 		*
 		* @param shaderAssets Vector of shader assets.
 		* @param size Size of the checkerboard quad.
 		*/

		DrawCheckerboardQuad(const std::vector<std::shared_ptr<engine::graphics::ShaderAsset>> &shaderAssets, engine::core::i32 size);

		/**
 		* @brief Prepares to render the checkerboard quad.
 		*
 		* This is a placeholder for any necessary preparations before drawing.
 		*/

		void prepare() override;

		/**
 		* @brief Executes rendering of the checkerboard quad.
 		*
 		* Binds the shader program, sets its float size, binds the vertex array,
 		* and draws triangles based on the indices array size.
 		*/

		void execute() override;

		/**
 		* @brief Finishes the rendering process.
 		*
 		* This is a placeholder for any necessary cleanup after drawing.
 		*/

		void finish() override;
	};
}


//
// Created by cx9ps3 on 20.11.2023.
//

#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <graphics/buffers/VertexArray.hpp>
#include <graphics/render_commands/IRenderCommand.hpp>
#include <shaders/ShaderProgram.hpp>

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

	class DrawCheckerboardQuad : public engine::graphics::IRenderCommand
	{
	private:
		static constexpr engine::core::u32 indicesArraySize = 6;///< Array size of indices.
		static constexpr engine::core::u32 vertexArraySize = 20;///< Array size of vertices.

		// Each pair of values represents the (u, v) coordinates of the texture associated with the vertex.
		std::array<float, vertexArraySize> quadVertices = {
				1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
				1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				-1.0f, 1.0f, 0.0f, 0.0f, 1.0f};///< Array of vertex positions and texture coordinates.

		std::array<engine::core::u32, indicesArraySize> quadIndices = {
				0, 1, 3,
				1, 2, 3};///< Array of vertex indices forming the quad.

		// Shader program for rendering the quad.
		std::shared_ptr<engine::graphics::ShaderProgram> shaderProgram;

		std::shared_ptr<engine::graphics::VertexBuffer> vertexBuffer;	 ///< Buffer for storing vertices.
		std::shared_ptr<engine::graphics::VertexArray> vertexArray;		 ///< Array of vertex buffers.
		std::shared_ptr<engine::graphics::ElementsBuffer> elementsBuffer;///< Buffer for storing indices.

		glm::vec4 firstColor {1.0f};
		glm::vec4 secondColor {0.5f, 0.5f, 0.5f, 1.0f};
		glm::vec2 cellCount;
		glm::vec2 windowSize;

	public:
		/**
 		* @brief Constructor for the DrawCheckerboardQuad class.
 		*
 		* Initializes the DrawCheckerboardQuad object with given shader assets and size.
 		* It also sets the layout of the vertex buffer and adds it to the vertex array
 		* together with the elements buffer.
 		*
 		* @param shaderAssets Vector of shader assets.
 		* @param size Size of the checkerboard texture.
 		*/

		DrawCheckerboardQuad(const std::vector<std::shared_ptr<engine::graphics::ShaderAsset>> &shaderAssets, const glm::vec2 &size);

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

		/**
 		* @brief Sets the size of the window and recalculates cellCount based on new size.
 		*
 		* @details This function sets the size of the window to `newWindowSize` and
 		* then recalculates the `cellCount` attribute by dividing `newWindowSize` by 10.
 		*
 		* @param newWindowSize A const reference to the glm::vec2 object representing
 		* the new size of the window.
 		*
 		*/

		void setWindowSize(const glm::vec2 &newWindowSize);

		/**
 		* @brief Function to set colors for the DrawCheckerboardQuad.
 		* @details This function sets first and second color for drawing a checkerboard pattern.
 		*
 		* @param newFirstColor A glm::vec4 color representing the first color for the checkerboard pattern.
 		* @param newSecondColor A glm::vec4 color representing the second color for the checkerboard pattern.
 		*
 		*/

		void setColors(const glm::vec4 &newFirstColor, const glm::vec4 &newSecondColor);

		~DrawCheckerboardQuad() override = default;
	};
}// namespace hexen::editor::components::graphics

//
// Created by cx9ps3 on 26.12.2023.
//
#pragma once
#include "IRenderCommand.hpp"
#include <glm/glm.hpp>

namespace hexen::engine::graphics
{
	class ShaderProgram;
	class ShaderAsset;
	class VertexBuffer;
	class VertexArray;
	class ElementsBuffer;
	class Texture2D;
	class ImageAsset;

	/**
 	* @class DrawQuadCommand
 	* @brief A class that represents a drawing quad.
 	* @details This class draw quad with texture.
 	* @extends IRenderCommand
 	*/

	class DrawQuadCommand : public IRenderCommand
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

		std::shared_ptr<ShaderProgram> shaderProgram;
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<ElementsBuffer> elementsBuffer;
		std::shared_ptr<VertexArray> vertexArray;
		std::shared_ptr<Texture2D> mainTexture;

		glm::mat4 transform;
		glm::mat4 view;
		glm::mat4 projection;

	public:
		/**
		 * @brief Constructor for class DrawQuadCommand.
		 * @param shaderAssets - shaders which applied to quad.
		 * @param textureImage - texture which be drawing on quad.
		 */
		explicit DrawQuadCommand(const std::vector<std::shared_ptr<ShaderAsset>> &shaderAssets, const std::shared_ptr<ImageAsset> &textureImage);

		/**
     	* @brief Execute the drawing a quad.
     	*/

		void execute() override;

		/**
     	* @brief Prepare for drawing quad.
     	*/

		void prepare() override;

		/**
     	* @brief Finish the draw command.
     	*/

		void finish() override;

		/**
		 * @brief Set view and projection matrices for drawing quad
		 *
		 * @tparam T - matrices type.
		 * @param newView - view matrix from camera.
		 * @param newProjection - projection matrix from camera.Projection can be orthogonal or perspective.
		 */

		template<class T>
		void updateViewAndProjectionMatrices(T &&newView, T &&newProjection)
		{
			view = std::forward<T>(newView);
			projection = std::forward<T>(newProjection);
		}

		/**
		 * @brief Set transform matrix for quad.
		 *
		 * @tparam T - matrix type.
		 * @param newTransform - new transform matrix which represents quad position, rotation and scale in space.
		 */

		template<class T>
		void updateTransformMatrix(T &&newTransform)
		{
			transform = std::forward<T>(newTransform);
		}
	};
}// namespace hexen::engine::graphics

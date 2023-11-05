//
// Created by cx9ps3 on 23.10.2023.
//

#pragma once
#include "IRenderCommand.hpp"
#include <glm/glm.hpp>
#include <utility>
#include <vector>

namespace hexen::engine::components
{
	class TransformComponent;
}
namespace hexen::engine::graphics
{
	class ShaderProgram;
	class ShaderAsset;
	class VertexArray;
	class VertexBuffer;
	class TextureArray;
	/**
 	* @struct QuadVertex
 	* @brief This struct represents a quad vertex with position, texture coordinates, and texture index.
 	*/

	struct QuadVertex
	{
		glm::vec3 position;			 ///< Position of the quad vertex.
		glm::vec2 textureCoordinates;///< Texture coordinates of the quad vertex.
		float textureIndex;			 ///< Texture index of the quad vertex.
	};

	/**
 	* @class Draw2DQuadsCommand
 	* @brief This class processes batch render commands for 2D quads.
 	* @extends IRenderCommand
 	*/

	class Draw2DQuadsCommand : public IRenderCommand
	{
	private:
		const core::u32 maxQuads = 10000;				///< Maximum number of quads allowed.
		const core::u32 maxVertices = maxQuads * 4;		///< Maximum number of vertices (maxQuads multiplied by 4 as each quad has 4 vertices).
		const core::u32 maxIndices = maxQuads * 6;		///< Maximum number of indices (maxQuads multiplied by 6 as each rectangle formed by a quad has 6 indices).
		static constexpr core::u32 maxTextureSlots = 32;///< Maximum number of texture slots.

		core::u32 indexCount {0};	   ///< Current count of indices.
		float textureSlotIndex = 0;///< Current index in the texture slot.

		std::shared_ptr<VertexBuffer> vertexBuffer;							 ///< Shared pointer to the vertex buffer.
		std::shared_ptr<VertexArray> vertexArray;							 ///< Shared pointer to the vertex array.
		std::shared_ptr<ShaderProgram> shaderProgram;						 ///< Shared pointer to the shader program.
		std::shared_ptr<TextureArray> textureArray;
		glm::vec2 maxTextureSize{16};
		std::unordered_map<std::string, float> textureSlots;

		QuadVertex *quadsVertexBase = nullptr;	 ///< Base pointer for quad vertices.
		QuadVertex *quadsVertexPointer = nullptr;///< Current pointer to the quad vertex.

		glm::mat4 projection;			 ///< Matrix for projection transformations.
		glm::mat4 view;					 ///< Matrix for view transformations.
		glm::vec4 quadVertexPositions[4];///< Positions of four vertices of a quad.

		/**
 		* @brief Initializes buffers and associates them with the vertex array.
 		*/

		void initializeBuffers();

		/**
 		* @brief Starts a new batch of quads.
 		*/

		void startBatch();

		/**
 		* @brief Initiates a new batch of quads after the current batch has been drawn.
 		*/

		void nextBatch();

		/**
 		* @brief Draws a batch of quads.
 		*/

		void drawBatch();

		using QuadData = std::pair<std::string, glm::mat4>;

		std::vector<QuadData> quadsData;

		void setDataToVertexBuffer();

		void addQuadDataToVertexBuffer(const QuadData &quadData);

	public:
		/**
 		* @brief Deletes quadsVertexBase.
 		*/

		~Draw2DQuadsCommand() override;

		/**
 		* @brief Constructs a Draw2DQuadsCommand and initializes buffers.
 		* @param shadersAssets initializer list with shader assets file.
 		*/

		Draw2DQuadsCommand(const std::initializer_list<std::shared_ptr<ShaderAsset>> &shadersAssets);

		/**
 		* @brief Constructs a Draw2DQuadsCommand and initializes buffers.
 		* @param pathsToShaders The vector of shader assets file.
 		*/

		explicit Draw2DQuadsCommand(const std::vector<std::shared_ptr<ShaderAsset>> &shadersAssets);

		/**
 		* @brief Adds a quad to the batch being processed. If the maximum number of indices has been reached, a new batch is started.
 		* @param texture Shared pointer to the texture of the quad
 		* @param transform Transforms to apply to the quad
 		*/
 		//TODO: change string to Texture asset
		void addQuad(const std::string &pathToTexture, const glm::mat4 &transform);

		/**
 		* @brief Prepares for the draw command by binding the shader program and setting matrices.
 		*/

		void prepare() override;

		/**
 		* @brief Executes the drawing of a batch of quads.
 		*/

		void execute() override;

		/**
 		* @brief Placeholder for future draw command completion tasks.
 		*/

		void finish() override;

		/**
 		* @brief Update the view and projection matrices for the Draw2DQuadsCommand
 		*
 		* This function allows you to set the current view and projection matrices in the Draw2DQuadsCommand. The method uses an r-value reference for performance
 		* reasons since copying large matrices can be expensive.
 		*
 		* @param view An r-value reference to the new view matrix.
 		* @param projection An r-value reference to the new projection matrix.
 		*
 		*/

		void updateViewAndProjectionMatrices(glm::mat4 &&view, glm::mat4 &&projection);
	};
}// namespace hexen::engine::graphics

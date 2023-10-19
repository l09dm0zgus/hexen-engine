//
// Created by cx9ps3 on 19.10.2023.
//

#pragma once
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <graphics/buffers/VertexArray.hpp>
#include <graphics/render_commands/IRenderCommand.hpp>

namespace hexen::editor::graphics
{
	/**
 	* @struct RenderGridData
 	* @brief The RenderGridData structure is used for storing rendering data.
 	*
 	* It contains pointers to both vertices and indices data along with their sizes,
 	* as well as the count of lines to be rendered.
 	*/

	struct RenderGridData
	{

		/**
     	* @brief Constructor that initializes vertices and indices from given vectors.
     	*
     	* @param verticesVector Vector of vertices data.
     	* @param indicesVector Vector of indices data.
     	*/

		RenderGridData(const std::vector<glm::vec3> &verticesVector, const std::vector<glm::uvec4> &indicesVector);

		float *vertices; ///< Pointer to the vertices data.
		hexen::engine::core::u32 verticesSize; ///< Size of the vertices data.
		hexen::engine::core::u32 *indices; ///< Pointer to the indices data.
		hexen::engine::core::u32 indicesSize; ///< Size of the indices data.
		engine::core::u32 countOfLines; ///< The count of lines to be rendered.
	};;

	/**
 	* @class DrawGridCommand
 	* @brief A command for drawing a grid in the Hexen editor.
 	*
 	* @extends IRenderCommand
 	*/

	class DrawGridCommand : public engine::graphics::IRenderCommand
	{
	private:
		std::shared_ptr<engine::graphics::VertexBuffer> vertexBuffer;
		std::unique_ptr<engine::graphics::VertexArray> vertexArray;
		std::shared_ptr<engine::graphics::ElementsBuffer> elementsBuffer;
		hexen::engine::core::u32 countOfLines;
	public:

		/**
     	* @brief Constructor that initializes vertexArray, elementsBuffer and vertexBuffer using provided RenderGridData.
     	* It also sets layout for vertexBuffer and countOfLines.
     	* @param renderGridData A RenderGridData containing data for initializing buffers and setting up the layout
     	*/

		explicit DrawGridCommand(const RenderGridData& renderGridData);

		/**
     	* @brief Prepares a rendering by binding vertexArray.
     	*/

		void prepare() override;

		/**
     	* @brief Executes a command to draw lines.
     	*/

		void execute() override;

		/**
     	* @brief Finishes a rendering by unbinding vertexArray.
     	*/

		void finish() override;

		~DrawGridCommand() override = default;
	};

}

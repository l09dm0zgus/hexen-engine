//
// Created by cx9ps3 on 19.10.2023.
//

#pragma once
#include <shaders/ShaderProgram.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <graphics/buffers/VertexArray.hpp>
#include <graphics/render_commands/IRenderCommand.hpp>

namespace hexen::editor::components::graphics
{
	class GridComponent;

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
 		* @brief Construct a new Render Grid Data object.
 		*
 		* This constructor initializes the members of the RenderGridData object, including shader assets, color, vertices, indices,
 		* vertices size, indices size and count of lines. It uses the provided vectors of vertices, indices and shader assets and
 		* the glm::vec3 color. It also adds the constructor to the HEXEN profile.
 		*
 		* @param verticesVector The vector of vertices of type glm::vec3. The memory address of the first element is assigned to the
 		* vertices pointer after removing its constantness.
 		* @param indicesVector The vector of indices of type glm::uvec4. The memory address of the first element is assigned to the
 		* indices pointer after removing its constantness.
 		* @param shaderAssets Vector of shared pointers to ShaderAsset objects from the engine::graphics namespace.
 		* @param color The glm::vec3 color to be used in rendering.
 		*
 		* @note The memory addresses of the vertices and indices vectors' first elements are obtained using glm::value_ptr() and then
 		* casted to non-const using const_cast<> because glm::value_ptr() returns a const pointer.
 		*
 		* Member 'verticesSize' stores the total size in bytes of all vertex data (size of the vertices vector multiplied by the size
 		* of glm::vec3).
 		* Member 'indicesSize' stores the total size in bytes of all index data (size of the indices vector multiplied by the size
 		* of glm::uvec4).
 		*
 		* Member 'countOfLines' stores the total number of lines, which is the size of the indices vector multiplied by 4.
	 	*/

		RenderGridData(const std::vector<glm::vec3> &verticesVector, const std::vector<glm::uvec4> &indicesVector , const std::vector<std::shared_ptr<engine::graphics::ShaderAsset>>& shaderAssets, const glm::vec3& color);

		float *vertices; ///< Pointer to the vertices data.
		hexen::engine::core::u32 verticesSize; ///< Size of the vertices data.
		hexen::engine::core::u32 *indices; ///< Pointer to the indices data.
		hexen::engine::core::u32 indicesSize; ///< Size of the indices data.
		engine::core::u32 countOfLines; ///< The count of lines to be rendered.
		std::vector<std::shared_ptr<engine::graphics::ShaderAsset>> shaderAssets; ///< Vector of shaders assets.
		glm::vec3 color; ///< Vector of RGB values for grid color.
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
		std::shared_ptr<engine::graphics::VertexBuffer> vertexBuffer; ///< Shared pointer to a VertexBuffer.
		std::unique_ptr<engine::graphics::VertexArray> vertexArray; ///< Unique pointer to a VertexArray.
		std::shared_ptr<engine::graphics::ElementsBuffer> elementsBuffer; ///< Shared Pointer to a ElementsBuffer.
		std::shared_ptr<hexen::engine::graphics::ShaderProgram> shaderProgram {nullptr}; ///< Shared Pointer to a ShaderProgram; initially nullptr.
		hexen::engine::core::u32 countOfLines; ///< Number of lines to draw.

		glm::vec3 color;
		glm::mat4 view{1};
		glm::mat4 projection{1};
		glm::mat4 transform{1};

		friend class GridComponent;
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

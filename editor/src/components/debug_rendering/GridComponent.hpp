//
// Created by cx9ps3 on 13.07.2023.
//

#pragma once
#include "DrawGridCommand.hpp"
#include <components/Component.hpp>
#include <components/ComponentContainer.hpp>
#include <entity/scene/Grid.hpp>
#include <graphics/render_commands/RenderPipeline.hpp>
#include <graphics/shaders/ShaderProgram.hpp>

namespace hexen::editor::components::graphics
{
	/**
 	* @class GridComponent
 	*
 	* @brief The GridComponent class renders a debug grid using the provided vertex and fragment shader paths.
 	*
 	* This component is used to render a debug grid in a 3D scene for debugging purposes. It requires vertex and fragment shader
 	* paths to be provided to properly render the grid. The grid is rendered using a vertex shader for vertex transformation
 	* and a fragment shader for fragment coloring.
 	* @extends Component
 	*/

	class GridComponent : public hexen::engine::components::Component
	{
		HEXEN_REGISTER_COMPONENT(GridComponent);
	private:
		glm::vec3 color {1.0f,0.0f, 0.0f};

		/**
     	* @brief Represents a grid structure.
     	*
     	* The Grid class represents a rectangular grid composed of cells.
 	    */

		std::shared_ptr<hexen::engine::core::Grid> grid;
		std::shared_ptr<DrawGridCommand> drawGridCommand;
		std::vector<std::shared_ptr<engine::graphics::ShaderAsset>> shaderAssets;
		void resize();
	public:

		GridComponent() = default;
		~GridComponent() override = default;

		/**
     	* @brief Primary constructor of GridComponent.
     	*
     	* This function sets up a GridComponent with the specified color, size and unit size. It also receives paths to shaders
     	* which will be used to render the grid.
     	*
     	* @param shaderAssets A list of  shaders assets files.
     	* @param newColor The color of the grid.
     	* @param size The size of the grid.
     	* @param unitSize The size of a single unit (cell) in the grid.
     	*/

		explicit GridComponent(const std::vector<std::shared_ptr<engine::graphics::ShaderAsset>> &shaderAssets, const glm::vec3 &newColor, const glm::vec2 &size, const glm::vec2 &unitSize, hexen::engine::graphics::RenderPipelineID renderPipelineId  = hexen::engine::graphics::RenderPipelineID::MAIN_PIPELINE);

		/**
     	* @brief Sets the color of an grid.
     	*
     	* This function sets the color of an object to the specified color.
     	*
     	* @tparam T The type of the new color.
     	* @param newColor The new color to be set.
     	*/

		template<class T>
		void setColor(T &&newColor)
		{
			drawGridCommand->color = std::forward<T>(newColor);
		}

		/**
     	* @brief Sets the view and projection matrices.
     	*
     	* This function sets the value of the view and projection matrices which will be used by the shaders for rendering the grid.
     	*
     	* @param view The view matrix.
     	* @param projection The projection matrix.
     	*/

		void setViewAndProjectionMatrices(const glm::mat4 &view, const glm::mat4 &projection);

		/**
     	* @brief Sets the transform matrix.
     	*
     	* This function sets the transform matrix which will be used by the shaders to transform the vertices of the grid.
     	*
     	* @param transform The transform matrix.
     	*/

		void setTransformMatrix(const glm::mat4 &transform);

		/**
 		* @brief Sets new size for the grid and resizes the draw command.
 		*
 		* @param [in] newSize A 2D vector representing new size for the grid.
 		*/

		void setSize(const glm::vec2& newSize);

		/**
 		* @brief Sets new unit size for the grid and resizes the draw command.
 		*
 		* @param [in] newUnitSize A 2D vector representing new unit size for the grid.
 		*/

		void setUnitSize(const glm::vec2& newUnitSize);

		/**
 		* @brief Sets new line width for the draw command.
 		*
 		* @param [in] lineWidth New line width for the grid.
 		*/

		void setLineWidth(float  lineWidth);

		/**
  		* @brief Generates coordinates for vertices of the grid.
 		*
 		* @param [in] grid Shared pointer to the Grid object.
 		* @return A vector of 3D vectors representing grid vertices.
 		*/

		static std::vector<glm::vec3> createGridVertices(const std::shared_ptr<hexen::engine::core::Grid> &grid);

		/**
 		* @brief Generates indices for a grid.
 		*
 		* @param [in] grid Shared pointer to the Grid object.
 		* @return A vector of 4D unsigned vectors representing grid indices.
 		*/

		static std::vector<glm::uvec4> createGridIndices(const std::shared_ptr<hexen::engine::core::Grid> &grid);

	};
}// namespace hexen::editor::components::graphics

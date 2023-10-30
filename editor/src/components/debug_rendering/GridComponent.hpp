//
// Created by cx9ps3 on 13.07.2023.
//

#pragma once
#include <entity/scene/Grid.hpp>
#include <graphics/shaders/ShaderProgram.hpp>
#include "DrawGridCommand.hpp"
#include <components/Component.hpp>

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
	private:
		glm::vec3 color {1.0f,0.0f, 0.0f};

		/**
     	* @brief Represents a grid structure.
     	*
     	* The Grid class represents a rectangular grid composed of cells.
 	    */

		std::unique_ptr<hexen::engine::core::Grid> grid;
		std::shared_ptr<DrawGridCommand> drawGridCommand;

	public:
		GridComponent() = default;
		~GridComponent() override = default;

		/**
     	* @brief Primary constructor of GridComponent.
     	*
     	* This function sets up a GridComponent with the specified color, size and unit size. It also receives paths to shaders
     	* which will be used to render the grid.
     	*
     	* @param pathsToShaders A list of file paths to the shaders.
     	* @param newColor The color of the grid.
     	* @param size The size of the grid.
     	* @param unitSize The size of a single unit (cell) in the grid.
     	*/

		explicit GridComponent(const std::vector<std::string> &pathsToShaders, const glm::vec3 &newColor, const glm::vec2 &size, const glm::vec2 &unitSize);

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

	};
}// namespace hexen::editor::components::graphics

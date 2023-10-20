//
// Created by cx9ps3 on 13.07.2023.
//

#pragma once
#include <entity/scene/Grid.hpp>
#include <components/graphics/RenderComponent.hpp>
#include <graphics/shaders/ShaderProgram.hpp>

namespace hexen::editor::components::graphics
{
	/**
     * @class DebugGridComponent
     *
     * @brief The DebugGridComponent class renders a debug grid using the provided vertex and fragment shader paths.
     *
     * This component is used to render a debug grid in a 3D scene for debugging purposes. It requires vertex and fragment shader
     * paths to be provided to properly render the grid. The grid is rendered using a vertex shader for vertex transformation
     * and a fragment shader for fragment coloring.
     * @extends RenderComponent
     */

	class DebugGridComponent : public hexen::engine::components::graphics::RenderComponent
	{
	private:
		glm::vec3 color {1.0f,0.0f, 0.0f};

		/**
        * @brief Represents a grid structure.
        *
        * The Grid class represents a rectangular grid composed of cells.
        */

		std::unique_ptr<hexen::engine::core::Grid> grid;

		/**
        * @brief The shader program variable.
        *
        * This variable represents a shader program.
        * A shader program links multiple shader objects together to form a complete rendering pipeline.
        * This variable is initialized to nullptr.
        * Make sure to check for nullptr before using this variable to avoid null pointer access.
        */

		std::shared_ptr<hexen::engine::graphics::ShaderProgram> shaderProgram {nullptr};

		engine::core::u32 renderHandle;

	public:

		explicit DebugGridComponent(const std::vector<std::string> &pathsToShaders);

		/**
        * @brief Sets the color of an grid.
        *
        * This function sets the color of an object to the specified color.
        *
        * @tparam T The type of the new color.
        * @param newColor The new color to be set.
        *
        *
        */

		template<class T>
		void setColor(T &&newColor)
		{
			color = std::forward<T>(newColor);
		}

		/**
        * @brief Draws the grid.
        *
        * This method is responsible for drawing the object. The exact implementation
        * depends on the derived class. The method is marked as noexcept to indicate
        * that it does not throw any exceptions. It overrides a base class method.
        *
        * @note Please refer to the derived class documentation for more information
        *       on how the drawing is done.
        *
        */

		void draw() noexcept override;
	};
}// namespace hexen::editor::components::graphics

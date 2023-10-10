//
// Created by cx9ps3 on 13.07.2023.
//

#pragma once
#include "core/graphics/shaders/Shaders.hpp"
#include "entity/scene/Grid.hpp"
#include "graphics/buffers/GL/GLElementsBuffer.hpp"
#include "graphics/buffers/GL/GLVertexArray.hpp"
#include "graphics/buffers/GL/GLVertexAttributes.hpp"
#include "graphics/buffers/GL/GLVertexBuffer.hpp"
#include <components/graphics/RenderComponent.hpp>

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
     */

	class DebugGridComponent : public hexen::engine::components::graphics::RenderComponent
	{
	private:
		glm::vec3 color {0.0f, 1.0f, 0.0f};

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

		std::shared_ptr<hexen::engine::graphics::gl::shader::GLShaderProgram> shaderProgram {nullptr};

		/**
        * @brief Represents a Vertex Buffer Object (VBO).
        *
        * A VBO is a buffer object that stores vertices and other data that define a set of primitives.
        * It is commonly used in computer graphics to efficiently store and render geometric data on the GPU.
        */

		hexen::engine::graphics::gl::GLVertexBuffer VBO;
		/**
        * @brief The vertices variable represents a collection of vertices in a geometric shape.
        *
        * In geometry, a vertex is a point where two or more lines meet. This variable
        * is typically used to store and manipulate a set of vertices that define the
        * shape of an object, such as a polygon or a mesh.
        *
        * The data structure used to represent the vertices can vary depending on the
        * specific needs of the application. Typically, it can be an array, a list, or
        * any other suitable container data structure provided by the programming
        * language used.
        *
        *  Usage example:
        *
        * @code
        * std::vector<glm::vec3> vertices {
        *     {0.0f, 0.0f, 0.0f},
        *     {1.0f, 0.0f, 0.0f},
        *     {0.0f, 1.0f, 0.0f}
        * };
        * @endcode
        *
        * In the above example, a vector container is used to store a collection of
        * 3D vertices represented by `glm::vec3` objects. These vertices define a
        * triangle with coordinates (0, 0, 0), (1, 0, 0), and (0, 1, 0).
        *
        * It is important to note that the order and arrangement of the vertices matter,
        * as they determine the shape and appearance of the object. For example, the
        * above vertices define a counterclockwise winding order for the triangle.
        * Changing the order or the arrangement of the vertices may result in a
        * different shape or orientation.
        *
        * @see https://en.wikipedia.org/wiki/Vertex_(geometry)
        */

		std::vector<glm::vec3> vertices;

		std::vector<glm::uvec4> indices;

		/**
        * @brief Represents the EBO (Element Buffer Object) variable.
        *
        * The EBO variable is used to store indices for vertex data in OpenGL. It is typically used together
        * with a VAO (Vertex Array Object) and a VBO (Vertex Buffer Object) to render complex shapes.
        */

		hexen::engine::graphics::gl::GLElementsBuffer EBO;

		hexen::engine::graphics::gl::GLVertexAttributes attributes;

		/**
        * @brief Vertex Array Object
        *
        * This variable represents a Vertex Array Object (VAO) used in computer graphics programming.
        *
        * A Vertex Array Object (VAO) is an OpenGL object that stores all of the necessary information
        * needed to render a set of vertices. It encapsulates all the states needed to enable vertex
        * attributes and is used for efficient rendering of dynamic objects.
        */

		hexen::engine::graphics::gl::GLVertexArray VAO;
		hexen::engine::core::i32 lenght {0};

	public:
		/**
     	* @brief Construct a new DebugGridComponent
     	*
     	* This constructor builds a new DebugGridComponent with the provided vertex and fragment shader paths.
     	*
     	* @param vertexShaderPath The file path to the vertex shader to be used.
     	* @param fragmentShaderPath The file path to the fragment shader to be used.
     	*/

		DebugGridComponent(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

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

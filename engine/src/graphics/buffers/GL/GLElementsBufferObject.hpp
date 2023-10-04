//
// Created by cx9ps3 on 14.05.2023.
//
#pragma once

#include "../../../core/Types.hpp"
#include "GLRectangleData.hpp"
#include "glm/vec4.hpp"

namespace hexen::engine::graphics::gl
{
	/**
    * @class GLElementsBufferObject
    *
    * @brief Represents a buffer object for storing elements data.
    *
    * The GLElementsBufferObject class is responsible for managing a buffer object
    * used for storing elements data, such as vertex indices or primitive indices.
    *
    * The buffer object can be used in conjunction with other rendering components
    * to efficiently render element-based primitives, such as triangles or lines.
    *
    * This class provides a constructor that initializes the elements buffer object.
     */

	class GLElementsBufferObject
	{
	public:

		/**
 		* @brief Default constructor for the GLElementsBufferObject class.
 		*
 		* This constructor generates a new OpenGL Elements Buffer Object and stores its ID.
 		*/

		GLElementsBufferObject();

		/**
 		* @brief Destructor for the GLElementsBufferObject class.
 		*
 		* This destructor deletes the OpenGL Elements Buffer Object associated with this class instance.
 		*/

		~GLElementsBufferObject();

		/**
        * Binds the buffer object with the provided rectangle data.
        *
        * This function binds the buffer object with the specified rectangle data,
        * allowing subsequent rendering operations to use the vertex and fragment
        * data contained within the buffer object.
        *
        * @param rectangleData The rectangle data to bind the buffer object with.
        *
        * @see GLRectangleData
        */


		void bind(const GLRectangleData &rectangleData) const;

		/**
        * @brief Unbinds the elements buffer object.
        *
        * This function unbinds the elements buffer object currently bound to the rendering context.
        * It is recommended to call this function after finishing using the elements buffer object
        * to free up the rendering context resources and to avoid unexpected behavior.
        *
        * @note This function does not return any value.
        *
        * @see core::rend::GLElementsBufferObject
        */

		void unbind();

		/**
        * @brief Binds the indices to the GLElementsBufferObject.
        *
        * This method binds the provided indices to the GLElementsBufferObject.
        * The indices are used to specify the vertex connectivity for batch rendering.
        *
        * @param indices The vector of glm::uvec4 indices representing the vertex connectivity.
        *
        */

		void bind(const std::vector<glm::uvec4> &indices) const;

	private:
		core::u32 object {0};
	};
}// namespace hexen::engine::graphics::gl

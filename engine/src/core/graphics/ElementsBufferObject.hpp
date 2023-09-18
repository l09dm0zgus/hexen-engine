//
// Created by cx9ps3 on 14.05.2023.
//
#pragma once

#include "../Types.hpp"
#include "RectangleData.hpp"
#include <glm/vec4.hpp>

namespace hexen::engine::graphics::gl
{
	class ElementsBufferObject
	{
	public:
		/**
        * @class ElementsBufferObject
        *
        * @brief Represents a buffer object for storing elements data.
        *
        * The ElementsBufferObject class is responsible for managing a buffer object
        * used for storing elements data, such as vertex indices or primitive indices.
        *
        * The buffer object can be used in conjunction with other rendering components
        * to efficiently render element-based primitives, such as triangles or lines.
        *
        * This class provides a constructor that initializes the elements buffer object.
        */

		ElementsBufferObject();

		/**
        * @class ElementsBufferObject
        * @brief This class represents a buffer object for storing vertex element data in graphics rendering.
        *
        * The ElementsBufferObject class is responsible for managing a buffer object that stores vertex
        * element data used in graphics rendering. It provides functionality to create, bind, and delete
        * the buffer object, as well as to update the buffer with new data.
        */

		~ElementsBufferObject();

		/**
        * Binds the buffer object with the provided rectangle data.
        *
        * This function binds the buffer object with the specified rectangle data,
        * allowing subsequent rendering operations to use the vertex and fragment
        * data contained within the buffer object.
        *
        * @param rectangleData The rectangle data to bind the buffer object with.
        *
        * @see RectangleData
        */


		void bind(const RectangleData &rectangleData) const;

		/**
        * @brief Unbinds the elements buffer object.
        *
        * This function unbinds the elements buffer object currently bound to the rendering context.
        * It is recommended to call this function after finishing using the elements buffer object
        * to free up the rendering context resources and to avoid unexpected behavior.
        *
        * @note This function does not return any value.
        *
        * @see core::rend::ElementsBufferObject
        */

		void unbind();

		/**
        * @brief Binds the indices to the ElementsBufferObject.
        *
        * This method binds the provided indices to the ElementsBufferObject.
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

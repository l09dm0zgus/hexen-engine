//
// Created by cx9ps3 on 02.01.23.
//

#pragma once


#include "../../../core/Types.hpp"
#include "GLRectangleData.hpp"
#include "glm/glm.hpp"
#include <cstddef>
namespace hexen::engine::graphics::gl
{
	/**
    * @class GLVertexBufferObject
    *
    * @brief The GLVertexBufferObject class represents a vertex buffer object used in rendering vertex data.
    *
    * A vertex buffer object (VBO) is used to efficiently store vertex data in GPU memory. This class provides
    * functionality to create and manage a VBO.
    */

	class GLVertexBufferObject
	{
	public:

		/**
        * @brief Constructor for GLVertexBufferObject.
        *
        * Generates a new buffer object name and stores it in the member variable 'object'.
        * The buffer is not initialized; it has a name but it does not yet have a type or any data.
        */

		GLVertexBufferObject();

		/**
 		* @fn hexen::engine::graphics::gl::GLVertexBufferObject::GLVertexBufferObjectct()
		*
    	* @brief Destructor of GLVertexBufferObject class.
 		*
 		* This function deletes the buffer, releasing the memory that was used for this
 		* Vertex Buffer Object from the GPU.
 		*/

		~GLVertexBufferObject();

		/**
        * Binds the given GLRectangleData to the Vertex Buffer Object (VBO).
        *
        * @param rectangleData The GLRectangleData to bind.
        *
        */

		void bind(const GLRectangleData &rectangleData) const;

		/**
        * Binds a vertex buffer object (VBO) with the specified size and data.
        *
        * @param size The size of the data being bound in bytes.
        * @param data A pointer to the data being bound.
        */

		void bind(size_t size, core::vptr data) const;

		/**
        * @brief Binds a Vertex Buffer Object (VBO) to the current rendering context
        *        using the provided vertices.
        *
        * This method binds a VBO to the current rendering context and uploads the provided
        * vertices to the VBO. The VBO should be previously created and initialized
        * to allocate memory for the vertices. The vertices are stored in a provided
        * std::vector of glm::vec3 objects.
        *
        * @param vertices The std::vector containing the vertices to be bound to the VBO.
        *
        *
        */

		void bind(const std::vector<glm::vec3> &vertices);

		/**
        * @brief Unbinds the Vertex Buffer Object (VBO).
        *
        * This function unbinds the currently bound Vertex Buffer Object (VBO)
        * in the rendering context. Once unbound, any subsequent graphics operations
        * will not be affected by the previously bound VBO.
        *
        * @note It is important to unbind a VBO after you are finished using it,
        *       to avoid potential issues when rendering or modifying other objects.
        *
        * @see core::rend::GLVertexBufferObject::bind()
        */


		void unbind();

	private:
		core::u32 object {0};
	};
}// namespace hexen::engine::graphics::gl

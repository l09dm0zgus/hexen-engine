//
// Created by cx9ps3 on 14.05.2023.
//
#pragma once

#include <Types.hpp>
#include <glm/vec4.hpp>
#include "../Buffers.hpp"

namespace hexen::engine::graphics::gl
{
	/**
    * @class GLElementsBuffer
    *
    * @brief Represents a buffer object for storing elements data.
    * @extends hexen::graphics::ElementsBuffer
    * The GLElementsBuffer class is responsible for managing a buffer object
    * used for storing elements data, such as vertex indices or primitive indices.
    *
    * The buffer object can be used in conjunction with other rendering components
    * to efficiently render element-based primitives, such as triangles or lines.
    *
    * This class provides a constructor that initializes the elements buffer object.
     */

	class GLElementsBuffer : public ElementsBuffer
	{
	public:

		/**
    	* Constructor for the GLElementsBuffer class.
    	* @param indices Integer pointer that represents indices to vertices. Used to avoid data duplication.
    	* @param size The size of the buffer, in bytes @note correct size is count of indices multiply by sizeof(<indices type>) of indices type.
    	*
    	* This function generates a new OpenGL buffer object, binds it to the context as an element array buffer,
    	* and allocates memory in the GPU for the buffer, filling it with the provided indices data. Then it unbinds the buffer.
    	*/

		GLElementsBuffer(core::u32 *indices, core::u32 size);

		/**
		* Constructor for the GLElementsBuffer class.
		* @param size The size of the buffer, in bytes @note correct size is count of indices multiply by sizeof(<indices type>) of indices type.
		*
		* This function generates a new OpenGL buffer object, binds it to the context as an element array buffer,
		* and allocates memory in the GPU for the buffer.
		*/

		GLElementsBuffer(core::u32 size);

		/**
 		* @brief Destructor for the GLElementsBuffer class.
 		*
 		* This destructor deletes the OpenGL Elements Buffer Object associated with this class instance.
 		*/

		~GLElementsBuffer() override;

		/**
        * Binds the buffer object with the provided rectangle data.
        *
        * This function binds the buffer object with the specified rectangle data,
        * allowing subsequent rendering operations to use the vertex and fragment
        * data contained within the buffer object.
        *
        */


		void bind() const noexcept override;

		/**
        * @brief Unbinds the elements buffer object.
        *
        * This function unbinds the elements buffer object currently bound to the rendering context.
        * It is recommended to call this function after finishing using the elements buffer object
        * to free up the rendering context resources and to avoid unexpected behavior.
        *
        * @note This function does not return any value.
        *
        * @see core::rend::GLElementsBuffer
        */

		void unbind() const noexcept override;

		/**
		 * @brief This function sets data to the elements buffer.
		 *
		 * @param data This is a pointer to the data to be set.
		 * @param size This is the size of the data to be set.
		 *
		 * The function first binds the buffer to the `GL_ELEMENT_ARRAY_BUFFER` target.
		 * Then, it creates and initializes a buffer object's data store.
		*/

		void setData(const core::vptr data , core::u32 size) override;

	private:
		core::u32 object {0};
	};
}// namespace hexen::engine::graphics::gl

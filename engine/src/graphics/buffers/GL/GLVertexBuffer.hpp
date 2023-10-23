//
// Created by cx9ps3 on 02.01.23.
//

#pragma once
#include "../Buffers.hpp"
#include <Types.hpp>
#include <cstddef>


namespace hexen::engine::graphics::gl
{
	/**
    * @class GLVertexBuffer
    *
    * @brief The GLVertexBuffer class represents a vertex buffer object used in rendering vertex data.
    * @extends VertexBuffer
    * A vertex buffer object (VBO) is used to efficiently store vertex data in GPU memory. This class provides
    * functionality to create and manage a VBO.
    */

	class GLVertexBuffer : public VertexBuffer
	{
	public:

		/**
 		* @brief Class constructor that sets up an OpenGL vertex buffer object (VBO).
 		*
 		* This constructor generates a new VBO, binds it to the current context,
 		* populates it with data and finally unbinds it from the context.
 		*
 		* @param vertices An array of floating point values representing a vertex data.
 		* @param size The size of the vertex data in bytes. @note  correct size is count of vertices multiply by sizeof(<indices type>) of vertices type.
 		*/

		GLVertexBuffer(float *vertices, core::u32 size);

		/**
 		* @brief Construct a new GLVertexBuffer object
 		* @details Creates a new vertex buffer object (VBO) in the GPU memory and establishes it as the current buffer
 		*                  for future OpenGL function that operate on VBOs. The buffer data is not initialized during the creation.
 		*
 		* @param size The size in bytes of the VBO's new data store.
 		*
 		* @note The GL_DYNAMIC_DRAW flag is used, it is a hint that the data store contents will be modified repeatedly
 		*       and used many times while drawing.
 		*
 		* @warning The provided size must not be negative or an integer overflow may occur.
		*
 		*/

		explicit GLVertexBuffer(core::u32 size);

		/**
		*
    	* @brief Destructor of GLVertexBuffer class.
 		*
 		* This function deletes the buffer, releasing the memory that was used for this
 		* Vertex Buffer Object from the GPU.
 		*/

		~GLVertexBuffer() override;

		/**
 		* @brief A member function that binds the vertex buffer object to the current OpenGL context.
 		*
 		* This function is used whenever the vertex data stored in this buffer object is required for rendering.
 		*/

		void bind() const noexcept override;

		/**
 		* @brief A member function that unbinds the vertex buffer object from the current OpenGL context.
 		*
 		* After rendering the data, it is good practice to unbind the buffer to prevent accidental modification or misuse.
 		*/

		void unbind() const noexcept override;

		/**
 		* @brief Sets the layout of the buffer.
 		*
 		* This function overrides a virtual function from a base class.
 		*
 		* @param layout A constant reference to the layout object which we need to set for our buffer.
 		*/

		void setLayout(const BufferLayout& layout) override { bufferLayout = layout; }

		/**
 		* \brief Returns the current layout of the buffer.
 		*
 		* This function is declared as 'nodiscard' which means the compiler will warn us if we ignore the return value.
 		* This function is also declared as 'noexcept' which means it doesn't throw any exceptions.
 		*
 		* @return A constant reference to the current buffer layout.
 		*/

		[[nodiscard]]  const BufferLayout& getLayout() const noexcept override { return bufferLayout; };

		/**
 		* @brief This function sets data to the GLVertexBuffer in the GL of the graphics engine.
 		*
 		* @param data This is a pointer to the data to be set in the GLVertexBuffer.
 		* @param size This is the size of the data to be set.
 		*
 		* The function first binds the buffer to the `GL_ARRAY_BUFFER` target.
 		* Then, it creates and initializes a buffer object's data store.
		*/

		void setData(const core::vptr data, core::u32 size) override;

	private:
		core::u32 object {0};
		BufferLayout bufferLayout;
	};
}// namespace hexen::engine::graphics::gl

//
// Created by cx9ps3 on 06.10.2023.
//

#pragma once
#include <glm/vec2.hpp>
#include <core/memory_pool/AllocatedObject.hpp>

namespace hexen::engine::graphics
{
	/**
 	* This class represents a buffer of elements.
 	* @extends core::memory::AllocatedObject
 	* This class provides the means to bind or unbind the elements buffer, and it allows the creation of new ElementsBuffer instances.
 	*/

	class ElementsBuffer : public core::memory::AllocatedObject
	{
	public:
		/**
     	* @brief Default virtual destructor.
     	*
     	*/

		virtual ~ElementsBuffer() = default;

		/**
     	* @brief Static method to create a new instance of ElementsBuffer.
     	*
     	* @param indices Pointer to the list of indices.
     	* @param size The size of the indices array.
     	* @note correct size is count of indices multiply by sizeof(<indices type>) of indices type.
     	* @return A unique_ptr to the new ElementsBuffer instance.
     	*/

		static std::unique_ptr<ElementsBuffer> create(core::u32 *indices, core::u32 size);

		/**
     	* @brief Pure virtual method to bind the elements buffer.
     	*
     	* Details of this method will be determined by the derived class.
     	*/

		virtual void bind() const noexcept = 0;

		/**
     	* @brief Pure virtual method to unbind the elements buffer.
     	*
     	* Details of this method will be determined by the derived class.
     	*/

		virtual void unbind() const noexcept = 0;
	};

	/**
 	* @brief A VertexBuffer class that provides the methods for managing the vertex buffer behavior.
 	* This class is part of the core::memory namespace and inherits from the AllocatedObject class.
 	*/

	class VertexBuffer : public core::memory::AllocatedObject
	{
	public:
		/**
        * @brief Virtual destructor of the VertexBuffer class.
        */

		virtual ~VertexBuffer() = 0;

		/**
        * @brief Static method for creating a vertex buffer.
        * @param vertices A pointer to the array of vertices.
        * @param size The size of the vertex buffer.
        * @return A unique pointer to the created VertexBuffer object.
        */

		static std::unique_ptr<VertexBuffer> create(float *vertices, core::u32 size);

		/**
        * @brief Pure virtual method that binds the vertex buffer.
        */

		virtual void bind() const noexcept = 0;

		/**
        * @brief Pure virtual method that unbinds the vertex buffer.
        */

		virtual void unbind() const noexcept = 0;
	};

	/**
 	* @class FrameBuffer
 	* @brief A memory-allocated object that manages a frame buffer.
 	* @details Inherits from the AllocatedObject in the core::memory namespace.
 	*/

	class FrameBuffer : public core::memory::AllocatedObject
	{
	public:

		/**
     	* @brief Factory function to create a new FrameBuffer instance.
     	* @param size A glm::vec2 defining the size of the frame buffer.
     	* @return A std::unique_ptr to the newly created FrameBuffer.
     	*/

		static std::unique_ptr<FrameBuffer> create(const glm::vec2 &size);

		/**
     	* @brief Default destructor.
     	*/

		virtual ~FrameBuffer() = default;

		/**
     	* @brief Pure virtual function to bind the frame buffer.
     	*/

		virtual void bind() const noexcept = 0;

		/**
     	* @brief Pure virtual function to unbind the frame buffer.
     	*/

		virtual void unbind() const noexcept = 0;

		/**
     	* @brief Pure virtual function to set the size of the frame buffer.
     	* @param size A glm::vec2 defining the new size of the frame buffer.
	    */

		virtual void setSize(const glm::vec2 &size)  const = 0;

		/**
     	* @brief Pure virtual function to bind the render buffer.
     	*/

		virtual void bindRenderBuffer() = 0;

		/**
     	* @brief Pure virtual function to unbind the render buffer.
     	*/

		virtual void unbindRenderBuffer() = 0;
	};

}// namespace hexen::engine::graphics
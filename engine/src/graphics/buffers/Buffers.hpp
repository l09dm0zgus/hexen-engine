//
// Created by cx9ps3 on 06.10.2023.
//

#pragma once
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
}// namespace hexen::engine::graphics
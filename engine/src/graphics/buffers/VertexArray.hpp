//
// Created by cx9ps3 on 07.10.2023.
//

#pragma once
#include "Buffers.hpp"

namespace hexen::engine::graphics
{
	/**
 	* @class VertexArray
 	* @brief A class for managing vertex array objects.
 	*
 	* VertexArray is a core concept in OpenGL. This class provides a way to
 	* group multiple vertex buffers and an element buffer together. It extends
 	* from core::memory::AllocatedObject as part of the project's memory management.
 	*/

	class VertexArray : public core::memory::AllocatedObject
	{
	public:
		/**
     	* @brief Creates a VertexArray object and returns a unique pointer to it.
     	*
     	* This factory method is used for creating a new VertexArray object.
     	* @return A unique pointer to the newly created VertexArray object.
     	*/

		static std::unique_ptr<VertexArray> create();

		/// Destructor.
		virtual ~VertexArray() = default;

		/**
    	* @brief Bind the vertex array to the OpenGL context.
    	*
    	* This will make this vertex array the currently active array in the
    	* OpenGL state machine.
    	*/

		virtual void bind() const = 0;

		/**
    	* @brief Unbind the vertex array from the OpenGL context.
    	*
    	* This will unset this vertex array from being the currently active array.
    	*/

		virtual void unbind() const = 0;

		/**
    	* @brief Add a vertex buffer to the vertex array.
    	*
    	* Adds the given vertex buffer to the array, enabling the array to
    	* draw from its data.
    	* @param vertexBuffer A shared pointer to the VertexBuffer to add.
    	*/

		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) = 0;

		/**
    	* @brief Set the element buffer of the vertex array.
	    *
    	* Assigns a new ElementsBuffer to the VertexArray. The elements buffer describes
    	* how to traverse the vertices in the vertex buffer.
    	* @param newElementBuffer A shared pointer to the new ElementsBuffer to set.
    	*/

		virtual void setElementBuffer(const std::shared_ptr<ElementsBuffer> &newElementBuffer) = 0;
	};
}// namespace hexen::engine::graphics

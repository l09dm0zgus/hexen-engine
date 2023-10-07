//
// Created by cx9ps3 on 04.01.23.
//

#pragma once

#include <core/Types.hpp>
#include "../VertexArray.hpp"

namespace hexen::engine::graphics::gl
{
	/**
 	* @class GLVertexArray
 	* @brief A class representing a Vertex Array Object (VAO).
 	* @extends VertexArray
 	* This class encapsulates the functionality of a Vertex Array Object, providing methods for its creation, deletion, and use.
 	* The VAO is a high-level abstraction of the Vertex Buffer Object (VBO), simplifying the handling of large sets of complex vertex data.
 	*/

	class GLVertexArray : public VertexArray
	{
	public:

		/**
 		* @brief Default constructor for GLVertexArray.
 		* Generates a Vertex Array Object (VAO) and stores the identifier.
 		*/

		GLVertexArray();

		/**
 		* @brief Binds the Vertex Array Object.
 		* Binds the VAO for OpenGL operations, using its stored identifier.
 		*/

		void bind() const override;

		/**
 		* @brief Destructor for GLVertexArray.
 		* Deletes the VAO using its identifier.
 		*/

		~GLVertexArray() override;

		/**
	 	* @brief Unbinds the Vertex Array Object.
 		* Unbinds all VAOs so that none are currently active.
 		*/

		void unbind() const override;

		/**
    	* @brief Add a vertex buffer to the vertex array.
    	*
    	* Adds the given vertex buffer to the array, enabling the array to
    	* draw from its data.
    	* @param vertexBuffer A shared pointer to the VertexBuffer to add.
    	*/


		void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;

		/**
    	* @brief Set the element buffer of the vertex array.
	    *
    	* Assigns a new ElementsBuffer to the VertexArray. The elements buffer describes
    	* how to traverse the vertices in the vertex buffer.
    	* @param newElementBuffer A shared pointer to the new ElementsBuffer to set.
    	*/

		void setElementBuffer(const std::shared_ptr<ElementsBuffer>& newElementsBuffers) override;

	private:
		core::u32 object {0};
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::shared_ptr<ElementsBuffer> elementsBuffer;
	};

}// namespace hexen::engine::graphics::gl

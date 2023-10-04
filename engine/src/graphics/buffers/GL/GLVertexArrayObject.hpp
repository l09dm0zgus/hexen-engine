//
// Created by cx9ps3 on 04.01.23.
//

#pragma once

#include "../../../core/Types.hpp"
namespace hexen::engine::graphics::gl
{
	/**
 	* @class GLVertexArrayObject
 	* @brief A class representing a Vertex Array Object (VAO).
 	*
 	* This class encapsulates the functionality of a Vertex Array Object, providing methods for its creation, deletion, and use.
 	* The VAO is a high-level abstraction of the Vertex Buffer Object (VBO), simplifying the handling of large sets of complex vertex data.
 	*/

	class GLVertexArrayObject
	{
	public:

		/**
 		* @brief Default constructor for GLVertexArrayObject.
 		* Generates a Vertex Array Object (VAO) and stores the identifier.
 		*/

		GLVertexArrayObject();

		/**
 		* @brief Binds the Vertex Array Object.
 		* Binds the VAO for OpenGL operations, using its stored identifier.
 		*/

		void bind() const;

		/**
 		* @brief Destructor for GLVertexArrayObject.
 		* Deletes the VAO using its identifier.
 		*/

		~GLVertexArrayObject();

		/**
	 	* @brief Unbinds the Vertex Array Object.
 		* Unbinds all VAOs so that none are currently active.
 		*/

		void unbind();

	private:
		core::u32 object {0};
	};

}// namespace hexen::engine::graphics::gl

//
// Created by cx9ps3 on 03.01.23.
//

#pragma once

#include "../../../core/Types.hpp"
#include <cstddef>
namespace hexen::engine::graphics::gl
{

	/**
 	* @class GLVertexAttributes
 	* @brief This class is used for defining and managing an array of generic vertex attributes.
 	*/

	class GLVertexAttributes
	{
	public:

		/**
        * Defines an array of generic vertex attribute data.
        *
        * Adds a vertex attribute to the current program object.
        *
        * @param size The number of components per generic vertex attribute.
        * @param stride The byte offset between consecutive generic vertex attributes.
        * @param offset Offset of the first component of the first generic vertex attribute in the array.
        */

		void add(core::i32 size, core::i32 stride, core::i32 offset);

		/**
        * Defines an array of generic vertex attribute data with a specified type size.
        *
        * @param size The number of components per generic vertex attribute.
        * @param typeSize The byte size of the type of the generic vertex attribute.
        * @param offset Offset of the first component of the first generic vertex attribute in the array.
        */

		void add(core::i32 size, size_t typeSize, core::i32 offset);

		/**
        * Modifies the rate at which generic vertex attributes advance when rendering multiple instances.
        *
        * @param index The index of the generic vertex attribute to be modified.
        * @param divisor The number of instances that will pass between updates of the generic vertex attribute.
        */

		void vertexDivisor(core::i32 index, core::i32 divisor);

	private:

		/**
     	* @brief A variable to hold the attributes
     	*/

		core::i32 attributes {0};
	};

}// namespace hexen::engine::graphics::gl

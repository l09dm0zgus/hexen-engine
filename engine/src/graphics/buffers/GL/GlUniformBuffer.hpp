//
// Created by cx9ps3 on 09.10.2023.
//

#pragma once
#include "../Buffers.hpp"
namespace hexen::engine::graphics::gl
{
	/**
 	* @class GLUniformBuffer
 	* @brief A class that represents a uniform buffer in OpenGL
 	* @details The class abstracts the concept of an OpenGL uniform buffer object. The class extends from a UniformBuffer.
 	* @extends UniformBuffer
 	*/

	class GLUniformBuffer : public UniformBuffer
	{
	private:
		core::u32 object {0};
	public:

		/**
     	* @brief Constructor for the GLUniformBuffer class.
     	* @param size Size of the uniform buffer.
     	* @param binding Buffer binding point.
     	*/

		GLUniformBuffer(core::u32 size, core::u32 binding);

		/**
     	* @brief Destructor for the GLUniformBuffer class.
     	*/

		~GLUniformBuffer() override;

		/**
     	* @brief Method to set data for the uniform buffer.
     	* @param data Pointer to the data to be set.
     	* @param size Size of the data.
     	* @param offset Offset for the data in the buffer (default is 0).
     	*/

		void setData(const core::vptr data, core::u32 size, core::u32 offset = 0) override;
	};;
}


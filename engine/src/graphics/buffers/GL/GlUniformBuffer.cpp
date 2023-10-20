//
// Created by cx9ps3 on 09.10.2023.
//
#ifndef __ANDROID__
	#include "GL/glew.h"
#else
	#include <GLES3/gl31.h>
#endif

#include "GlUniformBuffer.hpp"
hexen::engine::graphics::gl::GLUniformBuffer::GLUniformBuffer(hexen::engine::core::u32 size, hexen::engine::core::u32 binding)
{
	HEXEN_ADD_TO_PROFILE();
	glCreateBuffers(1, &object);
	glNamedBufferData(object, size, nullptr, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, binding, object);
}
hexen::engine::graphics::gl::GLUniformBuffer::~GLUniformBuffer()
{
	HEXEN_ADD_TO_PROFILE();
	glDeleteBuffers(1, &object);
}
void hexen::engine::graphics::gl::GLUniformBuffer::setData(hexen::engine::core::vptr const data, hexen::engine::core::u32 size, hexen::engine::core::u32 offset)
{
	HEXEN_ADD_TO_PROFILE();
	glNamedBufferSubData(object, offset, size, data);
}

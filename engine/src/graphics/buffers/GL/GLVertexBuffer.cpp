//
// Created by cx9ps3 on 02.01.23.
//

#include "GLVertexBuffer.hpp"

#ifndef __ANDROID__
	#include <GL/glew.h>
#else
	#include <GLES3/gl31.h>
#endif


hexen::engine::graphics::gl::GLVertexBuffer::GLVertexBuffer(float *vertices, core::u32 size)
{
	HEXEN_ADD_TO_PROFILE();
	glGenBuffers(1, &object);
	glBindBuffer(GL_ARRAY_BUFFER, object);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

hexen::engine::graphics::gl::GLVertexBuffer::~GLVertexBuffer()
{
	HEXEN_ADD_TO_PROFILE();
	glDeleteBuffers(1, &object);
}

void hexen::engine::graphics::gl::GLVertexBuffer::bind() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	glBindBuffer(GL_ARRAY_BUFFER, object);
}

void hexen::engine::graphics::gl::GLVertexBuffer::unbind() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

hexen::engine::graphics::gl::GLVertexBuffer::GLVertexBuffer(hexen::engine::core::u32 size)
{
	HEXEN_ADD_TO_PROFILE();
	glGenBuffers(1, &object);
	glBindBuffer(GL_ARRAY_BUFFER, object);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

void hexen::engine::graphics::gl::GLVertexBuffer::setData(hexen::engine::core::vptr const data, hexen::engine::core::u32 size)
{
	HEXEN_ADD_TO_PROFILE();
	glBindBuffer(GL_ARRAY_BUFFER,object);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

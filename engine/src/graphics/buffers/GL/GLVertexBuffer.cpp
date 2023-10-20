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
	glGenBuffers(1, &object);
	glBindBuffer(GL_ARRAY_BUFFER, object);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

hexen::engine::graphics::gl::GLVertexBuffer::~GLVertexBuffer()
{
	glDeleteBuffers(1, &object);
}

void hexen::engine::graphics::gl::GLVertexBuffer::bind() const noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, object);
}

void hexen::engine::graphics::gl::GLVertexBuffer::unbind() const noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

hexen::engine::graphics::gl::GLVertexBuffer::GLVertexBuffer(hexen::engine::core::u32 size)
{
	glGenBuffers(1, &object);
	glBindBuffer(GL_ARRAY_BUFFER, object);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

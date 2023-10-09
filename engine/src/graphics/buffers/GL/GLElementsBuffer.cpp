//
// Created by cx9ps3 on 14.05.2023.
//

#ifndef __ANDROID__
	#include <GL/glew.h>
	#include <glm/gtc/type_ptr.hpp>
#else
	#include <GLES3/gl31.h>
    #include <glm/gtc/type_ptr.hpp>
#endif

#include "GLElementsBuffer.hpp"


hexen::engine::graphics::gl::GLElementsBuffer::GLElementsBuffer(hexen::engine::core::u32 *indices, hexen::engine::core::u32 size)
{
	glGenBuffers(1, &object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

hexen::engine::graphics::gl::GLElementsBuffer::~GLElementsBuffer()
{
	glDeleteBuffers(1, &object);
}

void hexen::engine::graphics::gl::GLElementsBuffer::bind() const noexcept
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object);
}

void hexen::engine::graphics::gl::GLElementsBuffer::unbind() const noexcept
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


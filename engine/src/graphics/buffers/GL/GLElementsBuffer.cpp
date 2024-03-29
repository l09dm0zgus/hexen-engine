//
// Created by cx9ps3 on 14.05.2023.
//

#ifndef __ANDROID__
	#include <GL/glew.h>
	#include <glm/gtc/type_ptr.hpp>
#else
	#include <GLES3/gl31.h>
#endif

#include "GLElementsBuffer.hpp"

#include <glm/gtc/type_ptr.hpp>

hexen::engine::graphics::gl::GLElementsBuffer::GLElementsBuffer(hexen::engine::core::u32 *indices, hexen::engine::core::u32 size)
{
	HEXEN_ADD_TO_PROFILE();
	glGenBuffers(1, &object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

hexen::engine::graphics::gl::GLElementsBuffer::GLElementsBuffer(core::u32 size)
{
	HEXEN_ADD_TO_PROFILE();
	glGenBuffers(1, &object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

hexen::engine::graphics::gl::GLElementsBuffer::~GLElementsBuffer()
{
	HEXEN_ADD_TO_PROFILE();
	glDeleteBuffers(1, &object);
}

void hexen::engine::graphics::gl::GLElementsBuffer::bind() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object);
}

void hexen::engine::graphics::gl::GLElementsBuffer::unbind() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void hexen::engine::graphics::gl::GLElementsBuffer::setData(const core::vptr data, core::u32 size)
{
	HEXEN_ADD_TO_PROFILE();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,object);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
}


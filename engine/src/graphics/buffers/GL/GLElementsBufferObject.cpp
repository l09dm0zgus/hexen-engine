//
// Created by cx9ps3 on 14.05.2023.
//

#ifndef __ANDROID__
	#include "GL/glew.h"
	#include "glm/gtc/type_ptr.hpp"
#else
	#include <GLES3/gl31.h>
    #include <glm/gtc/type_ptr.hpp>
#endif

#include "GLElementsBufferObject.hpp"


hexen::engine::graphics::gl::GLElementsBufferObject::GLElementsBufferObject()
{
	glGenBuffers(1, &object);
}

hexen::engine::graphics::gl::GLElementsBufferObject::~GLElementsBufferObject()
{
	glDeleteBuffers(1, &object);
}

void hexen::engine::graphics::gl::GLElementsBufferObject::bind(const hexen::engine::graphics::gl::GLRectangleData &rectangleData) const
{
	constexpr auto bufferSize = sizeof(float) * RectangleDataSizes::INDICES_ARRAY_SIZE;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, rectangleData.indices, GL_STATIC_DRAW);
}


void hexen::engine::graphics::gl::GLElementsBufferObject::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void hexen::engine::graphics::gl::GLElementsBufferObject::bind(const std::vector<glm::uvec4> &indices) const
{
	auto bufferSize = indices.size() * sizeof(glm::uvec4);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, glm::value_ptr(indices[0]), GL_STATIC_DRAW);
}

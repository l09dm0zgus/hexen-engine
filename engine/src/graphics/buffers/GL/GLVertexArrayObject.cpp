//
// Created by cx9ps3 on 04.01.23.
//

#include "GLVertexArrayObject.hpp"
#ifndef __ANDROID__
	#include "GL/glew.h"
#else
	#include <GLES3/gl31.h>
#endif
hexen::engine::graphics::gl::GLVertexArrayObject::GLVertexArrayObject()
{
	glGenVertexArrays(1, &object);
}

void hexen::engine::graphics::gl::GLVertexArrayObject::bind() const
{
	glBindVertexArray(object);
}

hexen::engine::graphics::gl::GLVertexArrayObject::~GLVertexArrayObject()
{
	glDeleteVertexArrays(1, &object);
}

void hexen::engine::graphics::gl::GLVertexArrayObject::unbind()
{
	glBindVertexArray(0);
}

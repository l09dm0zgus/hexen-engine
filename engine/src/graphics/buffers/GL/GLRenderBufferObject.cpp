//
// Created by cx9ps3 on 09.06.2023.
//

#include "GLRenderBufferObject.hpp"

#ifndef __ANDROID__
	#include "GL/glew.h"
#else
	#include <GLES3/gl31.h>
#endif


hexen::engine::graphics::gl::GLRenderBufferObject::GLRenderBufferObject()
{
	glGenRenderbuffers(1, &object);
}

hexen::engine::graphics::gl::GLRenderBufferObject::~GLRenderBufferObject()
{
	glDeleteRenderbuffers(1, &object);
}

hexen::engine::core::u32 hexen::engine::graphics::gl::GLRenderBufferObject::getID() const noexcept
{
	return object;
}

void hexen::engine::graphics::gl::GLRenderBufferObject::bind() const
{
	glBindRenderbuffer(GL_RENDERBUFFER, object);
}

void hexen::engine::graphics::gl::GLRenderBufferObject::unbind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

//
// Created by cx9ps3 on 09.06.2023.
//

#include "RenderBufferObject.hpp"

#ifndef __ANDROID__
	#include <GL/glew.h>
#else
	#include <GLES3/gl31.h>
#endif


hexen::engine::graphics::gl::RenderBufferObject::RenderBufferObject()
{
	glGenRenderbuffers(1, &object);
}


hexen::engine::graphics::gl::RenderBufferObject::~RenderBufferObject()
{
	glDeleteRenderbuffers(1, &object);
}

hexen::engine::core::u32 hexen::engine::graphics::gl::RenderBufferObject::getID() const noexcept
{
	return object;
}

void hexen::engine::graphics::gl::RenderBufferObject::bind() const
{
	glBindRenderbuffer(GL_RENDERBUFFER, object);
}

void hexen::engine::graphics::gl::RenderBufferObject::unbind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

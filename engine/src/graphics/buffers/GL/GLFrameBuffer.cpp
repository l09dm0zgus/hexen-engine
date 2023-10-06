//
// Created by cx9ps3 on 09.06.2023.
//
#ifndef __ANDROID__
	#include "GL/glew.h"
#else
	#include <GLES3/gl31.h>
#endif
#include "GLFrameBuffer.hpp"
#include "SDL3/SDL.h"


hexen::engine::graphics::gl::GLFrameBuffer::GLFrameBuffer(const glm::vec2 &size)
{
	glGenFramebuffers(1, &object);
	glBindFramebuffer(GL_FRAMEBUFFER, object);
	//setSize is virtual,call virtual function in constructor is very big no-no.
	renderBufferObject.bind();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject.getID());

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

hexen::engine::graphics::gl::GLFrameBuffer::~GLFrameBuffer()
{
	glDeleteFramebuffers(1, &object);
}

void hexen::engine::graphics::gl::GLFrameBuffer::bind() const noexcept
{
	glBindFramebuffer(GL_FRAMEBUFFER, object);
}

void hexen::engine::graphics::gl::GLFrameBuffer::unbind() const noexcept
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void hexen::engine::graphics::gl::GLFrameBuffer::setSize(const glm::vec2 &size) const
{
	renderBufferObject.bind();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject.getID());
}


void hexen::engine::graphics::gl::GLFrameBuffer::bindRenderBuffer()
{
	renderBufferObject.bind();
}

void hexen::engine::graphics::gl::GLFrameBuffer::unbindRenderBuffer()
{
	renderBufferObject.unbind();
}

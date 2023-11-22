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


hexen::engine::graphics::gl::GLFrameBuffer::GLFrameBuffer(const FrameBufferSpecification &specification) : bufferSpecification(specification)
{
	HEXEN_ADD_TO_PROFILE();
	create();
}

hexen::engine::graphics::gl::GLFrameBuffer::~GLFrameBuffer()
{
	HEXEN_ADD_TO_PROFILE();
	glDeleteFramebuffers(1, &object);
	glDeleteTextures(1,&colorAttachment);
	glDeleteTextures(1, &depthAttachment);
}

void hexen::engine::graphics::gl::GLFrameBuffer::bind() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	glBindFramebuffer(GL_FRAMEBUFFER, object);
}

void hexen::engine::graphics::gl::GLFrameBuffer::unbind() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void hexen::engine::graphics::gl::GLFrameBuffer::setSize(const glm::vec2 &size)
{
	HEXEN_ADD_TO_PROFILE();
	glDeleteFramebuffers(1, &object);
	glDeleteTextures(1,&colorAttachment);
	glDeleteTextures(1, &depthAttachment);

	bufferSpecification.size = size;
	create();
}

void hexen::engine::graphics::gl::GLFrameBuffer::create()
{
	HEXEN_ADD_TO_PROFILE();

	glCreateFramebuffers(1, &object);
	glBindFramebuffer(GL_FRAMEBUFFER, object);

	glCreateTextures(GL_TEXTURE_2D, 1, &colorAttachment);
	glBindTexture(GL_TEXTURE_2D, colorAttachment);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA32F,bufferSpecification.size.x,bufferSpecification.size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,colorAttachment,0);


	glCreateTextures(GL_TEXTURE_2D, 1, &depthAttachment);
	glBindTexture(GL_TEXTURE_2D,depthAttachment);

	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH24_STENCIL8,bufferSpecification.size.x,bufferSpecification.size.y,0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,depthAttachment,0);

	HEXEN_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE , "ERROR: GL Framebuffer isn't created!");

	glBindFramebuffer(GL_FRAMEBUFFER,0);
}

hexen::engine::core::u32 hexen::engine::graphics::gl::GLFrameBuffer::getColorAttachmentObject() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return colorAttachment;
}
const hexen::engine::graphics::FrameBufferSpecification &hexen::engine::graphics::gl::GLFrameBuffer::getSpecification() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return bufferSpecification;
}

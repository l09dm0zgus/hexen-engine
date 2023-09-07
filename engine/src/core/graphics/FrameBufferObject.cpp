//
// Created by cx9ps3 on 09.06.2023.
//
#ifndef  __ANDROID__
#include <GL/glew.h>
#else
#include <GLES3/gl31.h>
#endif
#include <SDL3/SDL.h>
#include "FrameBufferObject.hpp"


hexen::engine::graphics::gl::FrameBufferObject::FrameBufferObject()
{
    glGenFramebuffers(1,&object);
}


hexen::engine::graphics::gl::FrameBufferObject::~FrameBufferObject()
{
    glDeleteFramebuffers(1,&object);
}

void hexen::engine::graphics::gl::FrameBufferObject::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER,object);
}

void hexen::engine::graphics::gl::FrameBufferObject::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void hexen::engine::graphics::gl::FrameBufferObject::setSize(const glm::vec2 &size) const
{
    renderBufferObject.bind();
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject.getID());
}


void hexen::engine::graphics::gl::FrameBufferObject::bindRenderBuffer()
{
    renderBufferObject.bind();
}

void hexen::engine::graphics::gl::FrameBufferObject::unbindRenderBuffer()
{
    renderBufferObject.unbind();

}

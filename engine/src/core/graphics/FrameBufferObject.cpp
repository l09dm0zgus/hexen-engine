//
// Created by cx9ps3 on 09.06.2023.
//
#ifndef  __ANDROID__
#include <GL/glew.h>
#else
#include <GLES3/gl31.h>
#endif
#include <SDL3/SDL.h>
#include "FrameBufferObject.h"


core::rend::FrameBufferObject::FrameBufferObject()
{
    glGenFramebuffers(1,&object);
}


core::rend::FrameBufferObject::~FrameBufferObject()
{
    glDeleteFramebuffers(1,&object);
}

void core::rend::FrameBufferObject::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER,object);
}

void core::rend::FrameBufferObject::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void core::rend::FrameBufferObject::setSize(const glm::vec2 &size) const
{
    renderBufferObject.bind();
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject.getID());
}


void core::rend::FrameBufferObject::bindRenderBuffer()
{
    renderBufferObject.bind();
}

void core::rend::FrameBufferObject::unbindRenderBuffer()
{
    renderBufferObject.unbind();

}

//
// Created by cx9ps3 on 09.06.2023.
//
#ifndef  __ANDROID__
#include <GL/glew.h>
#else
#include <GLES3/gl31.h>
#endif

#include "FrameBufferObject.h"

core::rend::FrameBufferObject::FrameBufferObject()
{
    glGenFramebuffers(1,&object);
    bind();
    unbind();
}

core::rend::FrameBufferObject::~FrameBufferObject()
{
    glDeleteFramebuffers(1,&object);
}

void core::rend::FrameBufferObject::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER,object);
    renderBufferObject.bind();

}

void core::rend::FrameBufferObject::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    renderBufferObject.unbind();
}

void core::rend::FrameBufferObject::setSize(const glm::vec2 &size)
{
    renderBufferObject.bind();
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject.getID());
}

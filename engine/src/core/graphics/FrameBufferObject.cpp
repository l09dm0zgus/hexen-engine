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

}

core::rend::FrameBufferObject::~FrameBufferObject()
{
    glDeleteFramebuffers(1,&object);
}

void core::rend::FrameBufferObject::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER,object);
}

void core::rend::FrameBufferObject::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

//
// Created by cx9ps3 on 09.06.2023.
//

#include "RenderBufferObject.h"

#ifndef  __ANDROID__
#include <GL/glew.h>
#else
#include <GLES3/gl31.h>
#endif


core::rend::RenderBufferObject::RenderBufferObject()
{
    glGenRenderbuffers(1,&object);
}



core::rend::RenderBufferObject::~RenderBufferObject()
{
    glDeleteRenderbuffers(1,&object);
}

core::u32 core::rend::RenderBufferObject::getID() const noexcept
{
    return object;
}

void core::rend::RenderBufferObject::bind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, object);
}

void core::rend::RenderBufferObject::unbind()
{
    glBindRenderbuffer(GL_RENDERBUFFER,0);
}

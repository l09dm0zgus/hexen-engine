//
// Created by cx9ps3 on 09.06.2023.
//
#ifndef  __ANDROID__
#include <GL/glew.h>
#else
#include <GLES3/gl31.h>
#endif

#include "FrameBufferTexture.h"


core::u32 core::rend::FrameBufferTexture::getID() const noexcept
{
    return object;
}

void core::rend::FrameBufferTexture::resize(const glm::vec2 &size) const
{
    glBindTexture(GL_TEXTURE_2D, object);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, static_cast<i32>(size.x), static_cast<i32>(size.y), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, object, 0);
}



core::rend::FrameBufferTexture::FrameBufferTexture(const glm::vec2 &size)
{
    glGenTextures(1,&object);
    resize(size);
}

core::rend::FrameBufferTexture::~FrameBufferTexture()
{
    glDeleteTextures(1,&object);
}

void core::rend::FrameBufferTexture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

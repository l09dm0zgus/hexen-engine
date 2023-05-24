//
// Created by cx9ps3 on 14.05.2023.
//

#ifndef  __ANDROID__
#include <GL/glew.h>
#else
#include <GLES3/gl31.h>
#endif
#include "ElementsBufferObject.h"

core::rend::ElementsBufferObject::ElementsBufferObject()
{
    glGenBuffers(1,&object);
}

core::rend::ElementsBufferObject::~ElementsBufferObject()
{
    glDeleteBuffers(1,&object);
}

void core::rend::ElementsBufferObject::bind(const core::rend::RectangleData &rectangleData) const
{
    constexpr auto bufferSize = sizeof(float) * RectangleDataSizes::INDICES_ARRAY_SIZE;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, rectangleData.indices, GL_STATIC_DRAW);
}

void core::rend::ElementsBufferObject::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

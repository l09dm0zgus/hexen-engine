//
// Created by cx9ps3 on 03.01.23.
//

#include "VertexAttributes.h"
#ifndef  __ANDROID__
#include "GL/glew.h"
#else
#include <GLES3/gl31.h>
#endif
void core::rend::VertexAttributes::add(i32 size,i32 stride,i32 offset)
{
    glVertexAttribPointer(attributes, size, GL_FLOAT, GL_FALSE,static_cast<int>(stride * sizeof(float)), (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(attributes);
    attributes++;
}

void core::rend::VertexAttributes::add(i32 size, size_t typeSize, i32 offset)
{
    glVertexAttribPointer(attributes, size, GL_FLOAT, GL_FALSE,  static_cast<int>(typeSize), (void*)(offset));
    glEnableVertexAttribArray(attributes);
    attributes++;
}

void core::rend::VertexAttributes::vertexDivisor(i32 index, i32 divisor)
{
    glVertexAttribDivisor(index,divisor);
}

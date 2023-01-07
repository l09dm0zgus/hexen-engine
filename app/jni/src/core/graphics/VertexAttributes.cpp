//
// Created by cx9ps3 on 03.01.23.
//

#include "VertexAttributes.h"
#ifndef  __ANDROID__
#include <GL/glew.h>
#else
#include <GLES3/gl31.h>
#endif
void VertexAttributes::add(int size,int stride,int offset)
{
    glVertexAttribPointer(attributes, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(attributes);
    attributes++;
}

//
// Created by cx9ps3 on 04.01.23.
//

#include "VertexArrayObject.h"
#ifndef  __ANDROID__
#include <GL/glew.h>
#else
#include <GLES3/gl31.h>
#endif
VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1,&object);
}

void VertexArrayObject::bind()
{
    glBindVertexArray(object);

}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &object);
}

void VertexArrayObject::unbind()
{
    glBindVertexArray(0);
}

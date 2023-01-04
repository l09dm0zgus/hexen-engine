//
// Created by cx9ps3 on 04.01.23.
//

#include "VertexArrayObject.h"
#include <GLES3/gl31.h>
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

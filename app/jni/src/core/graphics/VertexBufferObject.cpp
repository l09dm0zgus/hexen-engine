//
// Created by cx9ps3 on 02.01.23.
//

#include "VertexBufferObject.h"
#ifndef  __ANDROID__
#include <GL/glew.h>
#else
#include <GLES3/gl31.h>
#endif

core::rend::VertexBufferObject::VertexBufferObject()
{
    glGenBuffers(1,&object);
}

core::rend::VertexBufferObject::~VertexBufferObject()
{
    glDeleteBuffers(1, &object);
}

void core::rend::VertexBufferObject::bind(RectangleVertices &vertices)
{
    glBindBuffer(GL_ARRAY_BUFFER,object);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices.data),vertices.data,GL_STATIC_DRAW);
}

void core::rend::VertexBufferObject::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void core::rend::VertexBufferObject::bind(size_t size, void *data)
{
    glBindBuffer(GL_ARRAY_BUFFER, object);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

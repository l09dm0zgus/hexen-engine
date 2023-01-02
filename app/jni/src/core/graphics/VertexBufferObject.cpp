//
// Created by cx9ps3 on 02.01.23.
//

#include "VertexBufferObject.h"
#include <GLES3/gl31.h>
VertexBufferObject::VertexBufferObject(RectangleVertices &vertices)
{
    glGenBuffers(1,&object);
    glBindBuffer(GL_ARRAY_BUFFER,object);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices.data()),vertices.data(),GL_STATIC_DRAW);

}

VertexBufferObject::~VertexBufferObject()
{
    glDeleteBuffers(1, &object);
}

//
// Created by cx9ps3 on 02.01.23.
//

#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VertexBufferObject.hpp"
#ifndef  __ANDROID__
#include "GL/glew.h"
#else
#include <GLES3/gl31.h>
#endif


hexen::engine::graphics::gl::VertexBufferObject::VertexBufferObject()
{
    glGenBuffers(1,&object);
}


hexen::engine::graphics::gl::VertexBufferObject::~VertexBufferObject()
{
    glDeleteBuffers(1, &object);
}



void hexen::engine::graphics::gl::VertexBufferObject::bind(const RectangleData &rectangleData) const
{
    constexpr auto bufferSize = sizeof(float) * RectangleDataSizes::VERTICES_ARRAY_SIZE;
    glBindBuffer(GL_ARRAY_BUFFER,object);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, rectangleData.vertices, GL_STATIC_DRAW);
}

void hexen::engine::graphics::gl::VertexBufferObject::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void hexen::engine::graphics::gl::VertexBufferObject::bind(size_t size, core::vptr data) const
{
    glBindBuffer(GL_ARRAY_BUFFER, object);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long>(size), data, GL_STATIC_DRAW);
}


void hexen::engine::graphics::gl::VertexBufferObject::bind(const std::vector<glm::vec3> &vertices)
{
    auto bufferSize = vertices.size() * sizeof(glm::vec3);
    glBindBuffer(GL_ARRAY_BUFFER, object);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long>(bufferSize),glm::value_ptr(vertices[0]) , GL_STATIC_DRAW);
}

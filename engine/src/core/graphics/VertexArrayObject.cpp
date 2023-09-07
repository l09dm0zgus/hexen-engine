//
// Created by cx9ps3 on 04.01.23.
//

#include "VertexArrayObject.hpp"
#ifndef  __ANDROID__
#include "GL/glew.h"
#else
#include <GLES3/gl31.h>
#endif
hexen::engine::graphics::gl::VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1,&object);
}

void hexen::engine::graphics::gl::VertexArrayObject::bind() const
{
    glBindVertexArray(object);

}

hexen::engine::graphics::gl::VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &object);
}

void hexen::engine::graphics::gl::VertexArrayObject::unbind()
{
    glBindVertexArray(0);
}

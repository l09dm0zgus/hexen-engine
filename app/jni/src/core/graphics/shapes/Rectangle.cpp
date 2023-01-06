//
// Created by cx9ps3 on 04.01.23.
//

#include "Rectangle.h"
#ifndef  __ANDROID__
#include <GL/glew.h>
#else
#include <GLES3/gl31.h>
#endif

Rectangle::Rectangle(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{
    shaderProgram = new ShaderProgram(vertexShaderPath,fragmentShaderPath);
    VAO =  new VertexArrayObject();
    VBO = new VertexBufferObject();
    VAO->bind();
    VBO->bind(vertices);
    attributes.add(3,3,0);
    VBO->unbind();
    VAO->unbind();

}
Rectangle::~Rectangle()
{
    delete shaderProgram;
    shaderProgram = nullptr;

    VAO->unbind();
    delete VAO;
    VAO = nullptr;

    delete VBO;
    VBO = nullptr;
}

void Rectangle::render()
{
    shaderProgram->use();
    VAO->bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

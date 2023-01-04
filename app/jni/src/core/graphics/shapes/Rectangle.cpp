//
// Created by cx9ps3 on 04.01.23.
//

#include "Rectangle.h"
#include "GLES3/gl31.h"

Rectangle::Rectangle(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{
    shaderProgram = new ShaderProgram(vertexShaderPath,fragmentShaderPath);
    VAO =  new VertexArrayObject();
    VAO->bind();
    VBO = new VertexBufferObject(vertices);
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

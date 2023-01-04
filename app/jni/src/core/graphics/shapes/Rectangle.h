//
// Created by cx9ps3 on 04.01.23.
//

#ifndef BATTLEBLAZE_RECTANGLE_H
#define BATTLEBLAZE_RECTANGLE_H
#include "../shaders/Shaders.h"
#include "../VertexBufferObject.h"
#include "../VertexArrayObject.h"
#include "../RectangleVertices.h"
class Rectangle
{
public:
    Rectangle(const std::string &vertexShaderPath , const std::string &fragmentShaderPath);
    ~Rectangle();
    void render();
private:
    ShaderProgram *shaderProgram{nullptr};
    VertexArrayObject *VAO{nullptr};
    VertexBufferObject *VBO{nullptr};
    RectangleVertices vertices;
};


#endif //BATTLEBLAZE_RECTANGLE_H

//
// Created by cx9ps3 on 04.01.23.
//

#ifndef BATTLEBLAZE_SPRITE_H
#define BATTLEBLAZE_SPRITE_H
#include "../shaders/Shaders.h"
#include "../VertexBufferObject.h"
#include "../VertexArrayObject.h"
#include "../RectangleVertices.h"
#include "../VertexAttributes.h"
#include "../texture/Texture.h"
#include <vector>

class Sprite
{
public:
    Sprite(const std::string &vertexShaderPath , const std::string &fragmentShaderPath);
    ~Sprite();
    void render();
    void addTexture(const std::string &pathToImage);
private:
    void bindTextures();
    std::vector<Texture*> textures;
    ShaderProgram *shaderProgram{nullptr};
    VertexArrayObject *VAO{nullptr};
    VertexBufferObject *VBO{nullptr};
    RectangleVertices vertices;
    VertexAttributes attributes;
};


#endif //BATTLEBLAZE_SPRITE_H

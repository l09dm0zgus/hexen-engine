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
#include "../../transform/Transform.h"
#include <vector>

class Sprite
{
public:
    Sprite(const std::string &vertexShaderPath , const std::string &fragmentShaderPath);
    virtual ~Sprite();
    virtual void render(const glm::mat4 &projection , const glm::mat4 &view) ;
    void addTexture(const std::string &pathToImage);
    void  setTransform(const Transform &transform);
    Transform getTransform();
private:
    Transform transform;
    std::vector<Texture*> textures;
    VertexBufferObject *VBO{nullptr};
    RectangleVertices vertices;
protected:
    VertexAttributes attributes;
    VertexArrayObject *VAO{nullptr};
    ShaderProgram *shaderProgram{nullptr};
    void bindTextures();
};


#endif //BATTLEBLAZE_SPRITE_H

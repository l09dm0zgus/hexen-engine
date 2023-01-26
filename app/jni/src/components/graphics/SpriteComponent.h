//
// Created by cx9ps3 on 04.01.23.
//

#ifndef BATTLEBLAZE_SPRITECOMPONENT_H
#define BATTLEBLAZE_SPRITECOMPONENT_H
#include "../../core/graphics/shaders/Shaders.h"
#include "../../core/graphics/VertexBufferObject.h"
#include "../../core/graphics/VertexArrayObject.h"
#include "../../core/graphics/RectangleVertices.h"
#include "../../core/graphics/VertexAttributes.h"
#include "../../core/graphics/texture/Texture.h"
#include "../../core/transform/Transform.h"
#include <vector>
#include "RenderComponent.h"

class SpriteComponent : public RenderComponent
{
public:
    virtual ~SpriteComponent();
    void create(const std::string &vertexShaderPath , const std::string &fragmentShaderPath) override;
    void draw() override;
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


#endif //BATTLEBLAZE_SPRITECOMPONENT_H

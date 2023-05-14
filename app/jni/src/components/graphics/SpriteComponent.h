//
// Created by cx9ps3 on 04.01.23.
//

#ifndef BATTLEBLAZE_SPRITECOMPONENT_H
#define BATTLEBLAZE_SPRITECOMPONENT_H
#include "../../core/graphics/shaders/Shaders.h"
#include "../../core/graphics/VertexBufferObject.h"
#include "../../core/graphics/VertexArrayObject.h"
#include "../../core/graphics/RectangleData.h"
#include "../../core/graphics/VertexAttributes.h"
#include "../../core/graphics/texture/Texture.h"
#include "../../core/graphics/ElementsBufferObject.h"
#include <vector>
#include "RenderComponent.h"

namespace comp::rend
{
    class SpriteComponent : public RenderComponent
    {
    public:
        SpriteComponent(const std::string &vertexShaderPath , const std::string &fragmentShaderPath);
        ~SpriteComponent() = default;
        void draw() noexcept override;
        void addTexture(const std::string &pathToImage);
    private:
        std::vector<std::unique_ptr<core::rend::Texture>> textures;
        core::rend::VertexBufferObject VBO;
        core::rend::RectangleData vertices;
        core::rend::ElementsBufferObject EBO;
    protected:
        core::rend::VertexAttributes attributes;
        core::rend::VertexArrayObject VAO;
        std::shared_ptr<core::rend::shader::ShaderProgram> shaderProgram{nullptr};
        void bindTextures();
    };
}
#endif //BATTLEBLAZE_SPRITECOMPONENT_H

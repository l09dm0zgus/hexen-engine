//
// Created by cx9ps3 on 04.01.23.
//

#pragma once

#include "../../core/graphics/shaders/Shaders.h"
#include "../../core/graphics/VertexBufferObject.h"
#include "../../core/graphics/VertexArrayObject.h"
#include "../../core/graphics/RectangleData.h"
#include "../../core/graphics/VertexAttributes.h"
#include "../../core/graphics/texture/Texture.h"
#include "../../core/graphics/ElementsBufferObject.h"
#include <vector>
#include "RenderComponent.h"

namespace hexen::engine::components::graphics
{
    class SpriteComponent : public RenderComponent
    {
    public:
        SpriteComponent(const std::string &vertexShaderPath , const std::string &fragmentShaderPath);
        ~SpriteComponent() override = default;
        void draw() noexcept override;
        void addTexture(const std::string &pathToImage);
    private:
        std::vector<std::shared_ptr<hexen::engine::graphics::gl::Texture>> textures;
        hexen::engine::graphics::gl::VertexBufferObject VBO;
        hexen::engine::graphics::gl::RectangleData vertices;
        hexen::engine::graphics::gl::ElementsBufferObject EBO;
    protected:
        hexen::engine::graphics::gl::VertexAttributes attributes;
        hexen::engine::graphics::gl::VertexArrayObject VAO;
        std::shared_ptr<hexen::engine::graphics::gl::shader::ShaderProgram> shaderProgram{nullptr};
        void bindTextures();
    };
}

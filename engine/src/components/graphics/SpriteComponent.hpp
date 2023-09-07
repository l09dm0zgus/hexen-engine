//
// Created by cx9ps3 on 04.01.23.
//

#pragma once

#include "../../core/graphics/shaders/ShaderProgram.hpp"
#include "../../core/graphics/VertexBufferObject.hpp"
#include "../../core/graphics/VertexArrayObject.hpp"
#include "../../core/graphics/RectangleData.hpp"
#include "../../core/graphics/VertexAttributes.hpp"
#include "../../core/graphics/texture/Texture.hpp"
#include "../../core/graphics/ElementsBufferObject.hpp"
#include <vector>
#include "RenderComponent.hpp"

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

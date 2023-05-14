//
// Created by cx9ps3 on 04.01.23.
//

#include "SpriteComponent.h"
#ifndef  __ANDROID__
#include <GL/glew.h>
#else
#include <GLES3/gl31.h>
#endif

void comp::rend::SpriteComponent::draw() noexcept
{
    shaderProgram->setMatrix4Uniform("model" , getTransformMatrix());
    shaderProgram->setMatrix4Uniform("projection",getProjectionMatrix());
    shaderProgram->setMatrix4Uniform("view" , getViewMatrix());
    shaderProgram->use();
    bindTextures();
    VAO.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

}

void comp::rend::SpriteComponent::addTexture(const std::string &pathToImage)
{
    shaderProgram->use();
    shaderProgram->setIntUniform("textures[" +std::to_string(textures.size())+"]",static_cast<core::i32>(textures.size()));
    textures.push_back(core::mem::make_unique<core::rend::Texture>(pathToImage));
}

void comp::rend::SpriteComponent::bindTextures()
{
    for(int i = 0;i<textures.size();i++)
    {
        textures[0]->bind(i);
    }
}

comp::rend::SpriteComponent::SpriteComponent(const std::string &vertexShaderPath,const std::string &fragmentShaderPath)  : RenderComponent()
{
    textures.reserve(5);
    shaderProgram = core::mem::make_shared<core::rend::shader::ShaderProgram>(vertexShaderPath,fragmentShaderPath);
    VAO.bind();
    VBO.bind(vertices);
    EBO.bind(vertices);
    attributes.add(3,5,0);
    attributes.add(2,5,3);
    VBO.unbind();
    VAO.unbind();
    EBO.unbind();
}


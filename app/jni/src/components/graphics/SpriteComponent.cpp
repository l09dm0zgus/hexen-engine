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
    shaderProgram->setMatrix4Uniform("model" , transform.getTransformMatrix());
    shaderProgram->setMatrix4Uniform("projection",camera->getProjectionMatrix());
    shaderProgram->setMatrix4Uniform("view" , camera->getViewMatrix());
    shaderProgram->use();
    bindTextures();
    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
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

void comp::rend::SpriteComponent::setTransform(const Transform &transform)
{
    this->transform = transform;
}

Transform comp::rend::SpriteComponent::getTransform()
{
    return transform;
}

comp::rend::SpriteComponent::SpriteComponent(const std::string &vertexShaderPath,const std::string &fragmentShaderPath)
{
    textures.reserve(5);
    shaderProgram = core::mem::make_shared<core::rend::shader::ShaderProgram>(vertexShaderPath,fragmentShaderPath);
    VAO.bind();
    VBO.bind(vertices);
    attributes.add(3,5,0);
    attributes.add(2,5,3);
    VBO.unbind();
    VAO.unbind();
}


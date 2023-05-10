//
// Created by cx9ps3 on 04.01.23.
//

#include "SpriteComponent.h"
#ifndef  __ANDROID__
#include <GL/glew.h>
#else
#include <GLES3/gl31.h>
#endif

comp::rend::SpriteComponent::~SpriteComponent()
{
    delete shaderProgram;
    shaderProgram = nullptr;

    VAO->unbind();
    delete VAO;
    VAO = nullptr;

    delete VBO;
    VBO = nullptr;
}

void comp::rend::SpriteComponent::draw()
{
    shaderProgram->setMatrix4Uniform("model" , transform.getTransformMatrix());
    shaderProgram->setMatrix4Uniform("projection",camera->getProjectionMatrix());
    shaderProgram->setMatrix4Uniform("view" , camera->getViewMatrix());
    shaderProgram->use();
    bindTextures();
    VAO->bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void comp::rend::SpriteComponent::addTexture(const std::string &pathToImage)
{
    shaderProgram->use();
    shaderProgram->setIntUniform("textures[" +std::to_string(textures.size())+"]",textures.size());
    core::rend::Texture *texture = new core::rend::Texture();
    texture->create((pathToImage));
    textures.push_back(texture);
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

void comp::rend::SpriteComponent::create(const std::string &vertexShaderPath,const std::string &fragmentShaderPath)
{
    textures.reserve(5);
    shaderProgram = new core::rend::shader::ShaderProgram(vertexShaderPath,fragmentShaderPath);
    VAO =  new core::rend::VertexArrayObject();
    VBO = new core::rend::VertexBufferObject();
    VAO->bind();
    VBO->bind(vertices);
    attributes.add(3,5,0);
    attributes.add(2,5,3);
    VBO->unbind();
    VAO->unbind();
}

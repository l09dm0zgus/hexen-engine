//
// Created by cx9ps3 on 04.01.23.
//

#include "Sprite.h"
#ifndef  __ANDROID__
#include <GL/glew.h>
#else
#include <GLES3/gl31.h>
#endif

Sprite::Sprite(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{
    textures.reserve(5);
    shaderProgram = new ShaderProgram(vertexShaderPath,fragmentShaderPath);
    VAO =  new VertexArrayObject();
    VBO = new VertexBufferObject();
    VAO->bind();
    VBO->bind(vertices);
    attributes.add(3,5,0);
    attributes.add(2,5,3);
    VBO->unbind();
    VAO->unbind();

}
Sprite::~Sprite()
{
    delete shaderProgram;
    shaderProgram = nullptr;

    VAO->unbind();
    delete VAO;
    VAO = nullptr;

    delete VBO;
    VBO = nullptr;
}

void Sprite::render(const glm::mat4 &projection , const glm::mat4 &view)
{
    shaderProgram->setMatrix4Uniform("model" , transform.getTransformMatrix());
    shaderProgram->setMatrix4Uniform("projection",projection);
    shaderProgram->setMatrix4Uniform("view" , view);
    shaderProgram->use();
    bindTextures();
    VAO->bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Sprite::addTexture(const std::string &pathToImage)
{
    shaderProgram->use();
    shaderProgram->setIntUniform("textures[" +std::to_string(textures.size())+"]",textures.size());
    Texture *texture = new Texture(pathToImage);
    textures.push_back(texture);
}

void Sprite::bindTextures()
{
    for(int i = 0;i<textures.size();i++)
    {
        textures[0]->bind(i);
    }
}

void Sprite::setTransform(const Transform &transform)
{
    this->transform = transform;
}

Transform Sprite::getTransform()
{
    return transform;
}

//
// Created by cx9ps3 on 14.01.23.
//

#include "SpriteInstancedComponent.h"

#ifndef  __ANDROID__
#include <GL/glew.h>
#else
#include <GLES3/gl31.h>
#endif

void comp::rend::SpriteInstancedComponent::draw() noexcept
{

    shaderProgram->use();
    shaderProgram->setMatrix4Uniform("projection",getProjectionMatrix());
    shaderProgram->setMatrix4Uniform("view" , getViewMatrix());
    bindTextures();
    VAO.bind();
    glDrawElementsInstanced(GL_TRIANGLES, 0, 6, nullptr,numberOfInstances);
}

comp::rend::SpriteInstancedComponent::SpriteInstancedComponent(const std::string &vertexShaderPath,const std::string &fragmentShaderPath,core::i32 numberOfInstances, glm::mat4 *instancesMatrices)  : SpriteComponent(vertexShaderPath,fragmentShaderPath) , numberOfInstances(numberOfInstances),instancesMatrices(instancesMatrices)
{
    VAO.bind();
    instancesBuffer.bind(numberOfInstances*sizeof(glm::mat4), (void *) &instancesMatrices[0]);

    attributes.add(4,sizeof(glm::mat4),0);
    attributes.add(4,sizeof(glm::mat4),sizeof(glm::vec4));
    attributes.add(4,sizeof(glm::mat4),2 * sizeof(glm::vec4));
    attributes.add(4,sizeof(glm::mat4),3 * sizeof(glm::vec4));

    attributes.vertexDivisor(3,1);
    attributes.vertexDivisor(4,1);
    attributes.vertexDivisor(5,1);
    attributes.vertexDivisor(6,1);

    VAO.unbind();
    instancesBuffer.unbind();
}



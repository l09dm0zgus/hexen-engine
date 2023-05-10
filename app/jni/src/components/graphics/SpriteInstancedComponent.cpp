//
// Created by cx9ps3 on 14.01.23.
//

#include "SpriteInstancedComponent.h"

void comp::rend::SpriteInstancedComponent::draw()
{

    shaderProgram->use();
    shaderProgram->setMatrix4Uniform("projection",camera->getProjectionMatrix());
    shaderProgram->setMatrix4Uniform("view" , camera->getViewMatrix());
    bindTextures();
    VAO->bind();
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6,numberOfInstances);
}

void comp::rend::SpriteInstancedComponent::create(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{
    SpriteComponent::create(vertexShaderPath, fragmentShaderPath);
    instancesBuffer = new core::rend::VertexBufferObject();
    VAO->bind();
    instancesBuffer->bind(numberOfInstances*sizeof(glm::mat4), (void *) &instancesMatrices[0]);

    attributes.add(4,sizeof(glm::mat4),0);
    attributes.add(4,sizeof(glm::mat4),sizeof(glm::vec4));
    attributes.add(4,sizeof(glm::mat4),2 * sizeof(glm::vec4));
    attributes.add(4,sizeof(glm::mat4),3 * sizeof(glm::vec4));

    attributes.vertexDivisor(3,1);
    attributes.vertexDivisor(4,1);
    attributes.vertexDivisor(5,1);
    attributes.vertexDivisor(6,1);

    VAO->unbind();
    instancesBuffer->unbind();
}

void comp::rend::SpriteInstancedComponent::setNumberOfInstances(int numberOfInstances)
{
    this->numberOfInstances = numberOfInstances;
}

void comp::rend::SpriteInstancedComponent::setInstancesMatrices(glm::mat4 *instancesMatrices)
{
    this->instancesMatrices = instancesMatrices;
}

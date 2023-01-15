//
// Created by cx9ps3 on 14.01.23.
//

#include "SpriteInstanced.h"

SpriteInstanced::SpriteInstanced(const std::string &vertexShaderPath,const std::string &fragmentShaderPath, int numberOfInstances,const glm::mat4 *instancesMatrices) : Sprite(vertexShaderPath, fragmentShaderPath)
{
    this->numberOfInstances = numberOfInstances;
    instancesBuffer = new VertexBufferObject();
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

void SpriteInstanced::render(const glm::mat4 &projection, const glm::mat4 &view)
{

    shaderProgram->use();
    shaderProgram->setMatrix4Uniform("projection",projection);
    shaderProgram->setMatrix4Uniform("view" , view);
    bindTextures();
    VAO->bind();
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6,numberOfInstances);
}

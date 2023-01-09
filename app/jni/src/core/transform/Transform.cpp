//
// Created by cx9ps3 on 09.01.23.
//

#include "Transform.h"

void Transform::updateTransformMatrix()
{
    transformMatrix = glm::translate(transformMatrix,position);
    const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),rotation.x,glm::vec3(1.0f, 0.0f, 0.0f));
    const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),rotation.y,glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),rotation.z,glm::vec3(0.0f, 0.0f, 1.0f));

    const glm::mat4 rotionMatrix = transformY * transformX * transformZ;

    transformMatrix = transformMatrix * rotionMatrix;
    transformMatrix = glm::scale(transformMatrix,scale);
}

void Transform::setPosition(const glm::vec3 &newPosition)
{
    position = newPosition;
    updateTransformMatrix();
}

void Transform::setRotattion(const glm::vec3 &newRotation)
{
    rotation = newRotation;
    updateTransformMatrix();
}

void Transform::setScale(const glm::vec3 &newScale)
{
    scale = newScale;
    updateTransformMatrix();
}

glm::vec3 Transform::getScale()
{
    return scale;
}

glm::vec3 Transform::getPosition()
{
    return position;

}

glm::vec3 Transform::getRotation()
{
    return rotation;
}

glm::mat4 Transform::getTransformMatrix()
{
    return transformMatrix;
}

glm::mat4 Transform::getTransformMatrix(const glm::mat4 &parentTransform)
{
    transformMatrix = transformMatrix * parentTransform;
    return getTransformMatrix();
}


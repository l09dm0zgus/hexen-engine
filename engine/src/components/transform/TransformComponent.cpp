//
// Created by cx9ps3 on 09.01.23.
//

#include "TransformComponent.h"

void comp::TransformComponent::updateTransformMatrix()
{
    if(bIsDirty)
    {
        transformMatrix = glm::translate(transformMatrix,glm::vec3(position,1));

        transformMatrix = rotate(transformMatrix,rotation);

        transformMatrix = glm::scale(transformMatrix,glm::vec3(scale,1));

        bIsDirty = false;
    }

}

glm::vec2 comp::TransformComponent::getScale() const noexcept
{
    return scale;
}

glm::vec2 comp::TransformComponent::getPosition() const noexcept
{
    return position;
}

glm::vec2 comp::TransformComponent::getRotation() const noexcept
{
    return rotation;
}

glm::mat4 comp::TransformComponent::getTransformMatrix() const noexcept
{
    return transformMatrix;
}


void comp::TransformComponent::setLayer(float layer)
{
    zCoordinates.z = layer/layerDivider;
    bIsDirty = false;
}

inline glm::mat4 comp::TransformComponent::rotate(const glm::mat4 &transformMatrix, const glm::vec2 &rotation) const
{
    const auto transformX = glm::rotate(glm::mat4(1.0f),rotation.x,glm::vec3(1.0f, 0.0f, 0.0f));
    const auto transformY = glm::rotate(glm::mat4(1.0f),rotation.y,glm::vec3(0.0f, 1.0f, 0.0f));
    const auto transformZ = glm::rotate(glm::mat4(1.0f),zCoordinates.y,glm::vec3(0.0f, 0.0f, 1.0f));
    const auto rotationMatrix = transformY * transformX * transformZ;
    return transformMatrix * rotationMatrix;
}

float comp::TransformComponent::getLayer() const noexcept
{
    return layer;
}

comp::TransformComponent::TransformComponent(float layer) : layer(layer)
{
}

comp::TransformComponent::TransformComponent(const glm::vec2 &newPosition)
{
    setPosition(newPosition);
}

comp::TransformComponent::TransformComponent(const glm::mat4 &newTransform) : transformMatrix(newTransform)
{

}

comp::TransformComponent::TransformComponent(const glm::vec2 &newPosition,const glm::vec2 &newRotation)
{
    setPosition(newPosition);
    setRotation(newRotation);
}

comp::TransformComponent::TransformComponent(const glm::vec2 &newPosition,const glm::vec2 &newRotation,const glm::vec2 &newScale)
{
    setPosition(newPosition);
    setRotation(newRotation);
    setScale(newScale);
}

comp::TransformComponent::TransformComponent(const glm::vec2 &newPosition,const glm::vec2 &newRotation,const glm::vec2 &newScale, float layer) : TransformComponent(newPosition,newRotation,newScale)
{
    this->layer = layer;
}

void comp::TransformComponent::start()
{

}

void comp::TransformComponent::update(float deltaTime)
{

}

comp::TransformComponent::TransformComponent(const comp::TransformComponent &transformComponent): Component(transformComponent)
{
    copy(transformComponent);
}

comp::TransformComponent::TransformComponent(comp::TransformComponent &&transformComponent) noexcept
{
    move(std::move(transformComponent));
}

void comp::TransformComponent::copy(const comp::TransformComponent &transformComponent)
{
    setPosition(transformComponent.getPosition());
    setRotation(transformComponent.getRotation());
    setScale(transformComponent.getScale());
    setLayer(transformComponent.getLayer());
}

void comp::TransformComponent::move(comp::TransformComponent &&transformComponent) noexcept
{
    setPosition(transformComponent.getPosition());
    setRotation(transformComponent.getRotation());
    setScale(transformComponent.getScale());
    setLayer(transformComponent.getLayer());
}

comp::TransformComponent &comp::TransformComponent::operator=(const comp::TransformComponent &transformComponent)
{
    if(this == &transformComponent)
    {
        return *this;
    }
    copy(transformComponent);
    return *this;
}

comp::TransformComponent &comp::TransformComponent::operator=(comp::TransformComponent &&transformComponent) noexcept
{
    if(this == &transformComponent)
    {
        return *this;
    }
    move(std::move(transformComponent));
    return *this;
}

bool comp::TransformComponent::isDirty() const noexcept
{
    return bIsDirty;
}

template<class T>
void comp::TransformComponent::setScale(T &&newScale) noexcept
{
    scale = std::forward<T>(newScale);
    bIsDirty = true;
}

template<class T>
void comp::TransformComponent::setRotation(T &&newRotation) noexcept
{
    rotation = std::forward<T>(newRotation);
    bIsDirty = true;
}

template<class T>
void comp::TransformComponent::setPosition(T &&newPosition) noexcept
{
    position = std::forward<T>(newPosition);

    bIsDirty = true;
}



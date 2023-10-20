//
// Created by cx9ps3 on 09.01.23.
//

#include "TransformComponent.hpp"

void hexen::engine::components::TransformComponent::updateTransformMatrix()
{
	HEXEN_ADD_TO_PROFILE();
	if (bIsDirty)
	{
		transformMatrix = glm::translate(transformMatrix, glm::vec3(position, layer));

		transformMatrix = rotate(transformMatrix, rotation);

		transformMatrix = glm::scale(transformMatrix, glm::vec3(scale, 1));

		bIsDirty = false;
	}
}

glm::vec2 hexen::engine::components::TransformComponent::getScale() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return scale;
}

glm::vec2 hexen::engine::components::TransformComponent::getPosition() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return position;
}

glm::vec2 hexen::engine::components::TransformComponent::getRotation() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return rotation;
}

glm::mat4 hexen::engine::components::TransformComponent::getTransformMatrix() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return transformMatrix;
}


void hexen::engine::components::TransformComponent::setLayer(float layer)
{
	HEXEN_ADD_TO_PROFILE();
	this->layer = layer / layerDivider;
	bIsDirty = false;
}

inline glm::mat4 hexen::engine::components::TransformComponent::rotate(const glm::mat4 &transformMatrix, const glm::vec2 &rotation) const
{
	HEXEN_ADD_TO_PROFILE();
	const auto transformX = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	const auto transformY = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	const auto transformZ = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	const auto rotationMatrix = transformY * transformX * transformZ;
	return transformMatrix * rotationMatrix;
}

float hexen::engine::components::TransformComponent::getLayer() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return layer;
}

hexen::engine::components::TransformComponent::TransformComponent(float layer) : layer(layer)
{
}

hexen::engine::components::TransformComponent::TransformComponent(const glm::vec2 &newPosition)
{
	HEXEN_ADD_TO_PROFILE();
	setPosition(newPosition);
}

hexen::engine::components::TransformComponent::TransformComponent(const glm::mat4 &newTransform) : transformMatrix(newTransform)
{
	HEXEN_ADD_TO_PROFILE();
}

hexen::engine::components::TransformComponent::TransformComponent(const glm::vec2 &newPosition, const glm::vec2 &newRotation)
{
	HEXEN_ADD_TO_PROFILE();
	setPosition(newPosition);
	setRotation(newRotation);
}

hexen::engine::components::TransformComponent::TransformComponent(const glm::vec2 &newPosition, const glm::vec2 &newRotation, const glm::vec2 &newScale)
{
	HEXEN_ADD_TO_PROFILE();
	setPosition(newPosition);
	setRotation(newRotation);
	setScale(newScale);
}

hexen::engine::components::TransformComponent::TransformComponent(const glm::vec2 &newPosition, const glm::vec2 &newRotation, const glm::vec2 &newScale, float layer) : TransformComponent(newPosition, newRotation, newScale)
{
	HEXEN_ADD_TO_PROFILE();
	this->layer = layer;
}

void hexen::engine::components::TransformComponent::start()
{
}

void hexen::engine::components::TransformComponent::update(float deltaTime)
{
}

hexen::engine::components::TransformComponent::TransformComponent(const hexen::engine::components::TransformComponent &transformComponent) : Component(transformComponent)
{
	HEXEN_ADD_TO_PROFILE();
	copy(transformComponent);
}

hexen::engine::components::TransformComponent::TransformComponent(hexen::engine::components::TransformComponent &&transformComponent) noexcept
{
	HEXEN_ADD_TO_PROFILE();
	move(std::move(transformComponent));
}

void hexen::engine::components::TransformComponent::copy(const hexen::engine::components::TransformComponent &transformComponent)
{
	HEXEN_ADD_TO_PROFILE();
	setPosition(transformComponent.getPosition());
	setRotation(transformComponent.getRotation());
	setScale(transformComponent.getScale());
	setLayer(transformComponent.getLayer());
}

void hexen::engine::components::TransformComponent::move(hexen::engine::components::TransformComponent &&transformComponent) noexcept
{
	HEXEN_ADD_TO_PROFILE();
	setPosition(transformComponent.getPosition());
	setRotation(transformComponent.getRotation());
	setScale(transformComponent.getScale());
	setLayer(transformComponent.getLayer());
}

hexen::engine::components::TransformComponent &hexen::engine::components::TransformComponent::operator=(const hexen::engine::components::TransformComponent &transformComponent)
{
	HEXEN_ADD_TO_PROFILE();
	if (this == &transformComponent)
	{
		return *this;
	}
	copy(transformComponent);
	return *this;
}

hexen::engine::components::TransformComponent &hexen::engine::components::TransformComponent::operator=(hexen::engine::components::TransformComponent &&transformComponent) noexcept
{
	HEXEN_ADD_TO_PROFILE();
	if (this == &transformComponent)
	{
		return *this;
	}
	move(std::move(transformComponent));
	return *this;
}

bool hexen::engine::components::TransformComponent::isDirty() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return bIsDirty;
}

template<class T>
void hexen::engine::components::TransformComponent::setScale(T &&newScale) noexcept
{
	HEXEN_ADD_TO_PROFILE();
	scale = std::forward<T>(newScale);
	bIsDirty = true;
}

template<class T>
void hexen::engine::components::TransformComponent::setRotation(T &&newRotation) noexcept
{
	HEXEN_ADD_TO_PROFILE();
	rotation = std::forward<T>(newRotation);
	bIsDirty = true;
}

template<class T>
void hexen::engine::components::TransformComponent::setPosition(T &&newPosition) noexcept
{
	HEXEN_ADD_TO_PROFILE();
	position = std::forward<T>(newPosition);
	bIsDirty = true;
}

//
// Created by cx9ps3 on 26.01.23.
//
#include "RenderComponent.hpp"

void hexen::engine::components::graphics::RenderComponent::update(float deltaTime)
{
	draw();
}

void hexen::engine::components::graphics::RenderComponent::start()
{
}

glm::mat4 hexen::engine::components::graphics::RenderComponent::getProjectionMatrix() const noexcept
{
	return projection;
}

glm::mat4 hexen::engine::components::graphics::RenderComponent::getViewMatrix() const noexcept
{
	return view;
}

glm::mat4 hexen::engine::components::graphics::RenderComponent::getTransformMatrix() const noexcept
{
	return transform;
}

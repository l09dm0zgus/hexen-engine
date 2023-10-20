//
// Created by cx9ps3 on 26.01.23.
//
#include "RenderComponent.hpp"

void hexen::engine::components::graphics::RenderComponent::update(float deltaTime)
{
	HEXEN_ADD_TO_PROFILE();
	draw();
}

void hexen::engine::components::graphics::RenderComponent::start()
{
	HEXEN_ADD_TO_PROFILE();
}

glm::mat4 hexen::engine::components::graphics::RenderComponent::getProjectionMatrix() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return projection;
}

glm::mat4 hexen::engine::components::graphics::RenderComponent::getViewMatrix() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return view;
}

glm::mat4 hexen::engine::components::graphics::RenderComponent::getTransformMatrix() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return transform;
}

//
// Created by cx9ps3 on 26.01.23.
//
#include "RenderComponent.h"

void comp::rend::RenderComponent::update(float deltaTime)
{
    draw();
}

void comp::rend::RenderComponent::start()
{

}

glm::mat4 comp::rend::RenderComponent::getProjectionMatrix() const noexcept
{
    return projection;
}

glm::mat4 comp::rend::RenderComponent::getViewMatrix() const noexcept
{
    return view;
}

glm::mat4 comp::rend::RenderComponent::getTransformMatrix() const noexcept
{
    return transform;
}



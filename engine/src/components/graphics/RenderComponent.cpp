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

template<class T>
inline void comp::rend::RenderComponent::setTransformMatrix(T &&newTransform) noexcept
{
    transform = std::forward<T>(newTransform);
}

template<class T>
inline void comp::rend::RenderComponent::setViewMatrix(T &&newView) noexcept
{
    view = std::forward<T>(newView);
}

template<class T>
inline void comp::rend::RenderComponent::setProjectionMatrix(T &&newProjection) noexcept
{
    projection = std::forward<T>(newProjection);
}

//
// Created by cx9ps3 on 10.01.23.
//

#include "CameraComponent.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include <SDL3/SDL.h>
#include <GLES3/gl31.h>

void comp::CameraComponent::updateViewMatrix()
{
    view = glm::lookAt(position, position + cameraTarget, cameraUp);
}

comp::CameraComponent::CameraComponent(core::i32 viewportWidth, core::i32 viewportHeight, float FOV)
{
    glViewport(0,0,viewportWidth,viewportWidth);
    projection = glm::perspective(glm::radians(FOV), static_cast<float>(viewportWidth) / static_cast<float>(viewportHeight), 0.1f, 100.0f);
    SDL_Log("Viewport size width : %i , height : %i",viewportWidth,viewportHeight);
    updateViewMatrix();
}
template<class T>
void comp::CameraComponent::setPosition(T&& newPosition) noexcept
{
    position = std::forward<T>(newPosition);
    updateViewMatrix();
}

glm::mat4 comp::CameraComponent::getViewMatrix()
{
    return view;
}

glm::mat4 comp::CameraComponent::getProjectionMatrix()
{
    return projection;
}

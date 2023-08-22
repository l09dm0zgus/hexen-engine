//
// Created by cx9ps3 on 10.01.23.
//

#include "CameraComponent.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include <SDL3/SDL.h>
#ifndef  __ANDROID__
#include <GL/glew.h>
#else
#include <GLES3/gl31.h>
#endif

void comp::CameraComponent::updateViewMatrix()
{
    glm::vec3 direction;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cameraTarget = glm::normalize(direction);

    cameraRight = glm::normalize(glm::cross(cameraTarget, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraTarget));

    view = glm::lookAt(position, position + cameraTarget, cameraUp);
}

comp::CameraComponent::CameraComponent(core::i32 viewportWidth, core::i32 viewportHeight,float FOV)
{
    this->FOV = FOV;

    updateProjectionMatrix(viewportWidth,viewportHeight);
    updateViewMatrix();
}

glm::mat4 comp::CameraComponent::getViewMatrix()
{
    updateViewMatrix();
    return view;
}


glm::mat4 comp::CameraComponent::getProjectionMatrix()
{
    return projection;
}

void comp::CameraComponent::start()
{

}


void comp::CameraComponent::update(float deltaTime)
{
    this->deltaTime = deltaTime;
}


void comp::CameraComponent::move(float value)
{
    position += value * deltaTime * cameraTarget;
    updateViewMatrix();
}

void comp::CameraComponent::zoom(float value)
{
    position += glm::normalize(glm::cross(cameraTarget, cameraUp)) * value * deltaTime;
    updateViewMatrix();
}

void comp::CameraComponent::rotate(float yawAngle, float pitchAngle)
{
    yaw += yawAngle * deltaTime;
    pitch += pitchAngle * deltaTime;
    updateViewMatrix();
}


void comp::CameraComponent::updateProjectionMatrix(core::u32 newWindowWidth, core::u32 newWindowHeight)
{
    glViewport(0,0,newWindowWidth,newWindowHeight);

    SDL_Log("Viewport size width : %i , height : %i, FOV: %f",newWindowWidth,newWindowHeight,FOV);

    projection = glm::perspective(glm::radians(FOV), static_cast<float>(newWindowWidth) / static_cast<float>(newWindowHeight), 0.1f, 100.0f);
}

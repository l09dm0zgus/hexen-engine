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
    view = glm::lookAt(position, position + cameraTarget, cameraUp);
}



comp::CameraComponent::CameraComponent(core::i32 viewportWidth, core::i32 viewportHeight,float FOV)
{
    this->FOV = FOV;

    updateProjectionMatrix(viewportWidth,viewportHeight);

    SDL_Log("Viewport size width : %i , height : %i",viewportWidth,viewportHeight);
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
    glm::vec3 direction;

    direction.x = cos(glm::radians(yawAngle)) * cos(glm::radians(pitchAngle));
    direction.y = sin(glm::radians(pitchAngle));
    direction.z = sin(glm::radians(yawAngle)) * cos(glm::radians(pitchAngle));

    cameraTarget = glm::normalize(direction);
}


void comp::CameraComponent::updateProjectionMatrix(core::u32 newWindowWidth, core::u32 newWindowHeight)
{
    glViewport(0,0,newWindowWidth,newWindowHeight);
    projection = glm::perspective(glm::radians(FOV), static_cast<float>(newWindowWidth) / static_cast<float>(newWindowHeight), 0.1f, 100.0f);
}

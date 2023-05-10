//
// Created by cx9ps3 on 10.01.23.
//

#include "Camera.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include <SDL.h>
#include <GLES3/gl31.h>

void core::Camera::updateViewMatrix()
{
    view = glm::lookAt(position, position + cameraTarget, cameraUp);
}

core::Camera::Camera(int viewportWidth, int viewportHeight, float FOV)
{
    glViewport(0,0,viewportWidth,viewportWidth);
    projection = glm::perspective(glm::radians(FOV), (float)viewportWidth / viewportHeight, 0.1f, 100.0f);
    SDL_Log("Viewport size width : %i , height : %i",viewportWidth,viewportHeight);
    updateViewMatrix();
}

void core::Camera::setPosition(const glm::vec3 &newPosition)
{
    position = newPosition;
    updateViewMatrix();
}

glm::mat4 core::Camera::getViewMatrix()
{
    return view;
}

glm::mat4 core::Camera::getProjectionMatrix()
{
    return projection;
}

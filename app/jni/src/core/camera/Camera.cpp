//
// Created by cx9ps3 on 10.01.23.
//

#include "Camera.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include <SDL.h>
void Camera::updateViewMatrix()
{

    view = glm::lookAt(position, position + cameraTarget, cameraUp);

}

Camera::Camera(int viewportWidth, int viewportHeight, float FOV)
{
    projection = glm::perspective(glm::radians(FOV), (float)viewportWidth / viewportHeight, 0.1f, 100.0f);
    SDL_Log("Viewport size width : %i , height : %i",viewportWidth,viewportHeight);
    updateViewMatrix();
}

void Camera::setPosition(const glm::vec3 &newPosition)
{
    position = newPosition;
    updateViewMatrix();
}

glm::mat4 Camera::getViewMatrix() {
    return view;
}

glm::mat4 Camera::getProjectionMatrix() {
    return projection;
}

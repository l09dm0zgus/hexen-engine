//
// Created by cx9ps3 on 26.01.23.
//
#include "RenderComponent.h"

void RenderComponent::setCamera(Camera *camera)
{
    this->camera = camera;
}

void RenderComponent::update(float deltaTime)
{
    draw();
}

void RenderComponent::start()
{

}

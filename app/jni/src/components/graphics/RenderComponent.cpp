//
// Created by cx9ps3 on 26.01.23.
//
#include "RenderComponent.h"

void comp::rend::RenderComponent::setCamera(core::Camera *camera)
{
    this->camera = camera;
}

void comp::rend::RenderComponent::update(float deltaTime)
{
    draw();
}

void comp::rend::RenderComponent::start()
{

}

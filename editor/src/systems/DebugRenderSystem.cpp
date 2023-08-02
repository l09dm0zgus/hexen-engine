//
// Created by cx9ps3 on 13.07.2023.
//

#include <systems/TaskSystem.h>
#include <systems/RenderSystem.h>
#include "DebugRenderSystem.h"

edit::sys::DebugRenderSystem::DebugRenderSystem(core::u32 sizeOfVectors)
{

}

void edit::sys::DebugRenderSystem::start()
{

}

void edit::sys::DebugRenderSystem::render(float alpha)
{
    if (debugGridComponent != nullptr)
    {
        ::sys::TaskSystem::addTask<DebugRenderSystem,void,::comp::rend::RenderComponent*>(core::threading::TaskPriority::Normal, this,&DebugRenderSystem::updateModelMatrix,debugGridComponent.get());
        ::sys::TaskSystem::addTask<DebugRenderSystem,void,::comp::rend::RenderComponent*>(core::threading::TaskPriority::Normal, this,&DebugRenderSystem::updateViewAndProjectionMatrices,debugGridComponent.get());;
        ::sys::TaskSystem::addTask(core::threading::TaskPriority::Normal,debugGridComponent.get(),&comp::rend::DebugGridComponent::draw);
    }
}

void edit::sys::DebugRenderSystem::addDebugGrid()
{
    if(debugGridComponent == nullptr)
    {
        debugGridComponent = core::mem::make_shared<comp::rend::DebugGridComponent>("shaders/BaseVertexShader.glsl","shaders/DebugLineFragmentShader.glsl");
        debugGridTransform = core::mem::make_shared<::comp::TransformComponent>(glm::vec2{0.0f});
    }
}

void edit::sys::DebugRenderSystem::updateModelMatrix(::comp::rend::RenderComponent *renderComponent)
{
    renderComponent->setTransformMatrix(debugGridTransform->getTransformMatrix());
}

void edit::sys::DebugRenderSystem::updateViewAndProjectionMatrices(::comp::rend::RenderComponent *renderComponent)
{
    auto camera = ::sys::RenderSystem::getMainCamera();
    HEXEN_ASSERT(camera != nullptr , "Main camera is nullptr!\n");

    renderComponent->setProjectionMatrix(camera->getProjectionMatrix());
    renderComponent->setViewMatrix(camera->getViewMatrix());
}


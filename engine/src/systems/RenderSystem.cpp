//
// Created by cx9ps3 on 23.05.2023.
//

#include "RenderSystem.h"
#include <algorithm>
#include "TaskSystem.h"


std::vector<comp::rend::SpriteComponent> sys::RenderSystem::spritesComponent;

std::vector<comp::rend::SpriteInstancedComponent> sys::RenderSystem::instancedSpritesComponents;

std::vector<comp::TransformComponent> sys::RenderSystem::transformComponents;

std::vector<std::shared_ptr<comp::CameraComponent>> sys::RenderSystem::camerasComponents;

core::i32 sys::RenderSystem::mainCameraId{0};


sys::RenderSystem::RenderSystem(core::u32 sizeOfVectors)
{
    spritesComponent.reserve(sizeOfVectors);
    instancedSpritesComponents.reserve(sizeOfVectors);
    transformComponents.reserve(sizeOfVectors);
    camerasComponents.reserve(sizeOfVectors);
}

std::shared_ptr<comp::rend::SpriteComponent> sys::RenderSystem::createSpriteComponent(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{
    spritesComponent.emplace_back(vertexShaderPath,fragmentShaderPath);
    return std::shared_ptr<comp::rend::SpriteComponent>(&*spritesComponent.end());
}



std::shared_ptr<comp::rend::SpriteInstancedComponent> sys::RenderSystem::createSpriteInstancedSprite(const std::string &vertexShaderPath, const std::string &fragmentShaderPath, core::i32 numberOfInstances, glm::mat4 *instancesMatrices)
{
    instancedSpritesComponents.emplace_back(vertexShaderPath,fragmentShaderPath,numberOfInstances,instancesMatrices);
    return std::shared_ptr<comp::rend::SpriteInstancedComponent>(&*instancedSpritesComponents.end());
}

std::shared_ptr<comp::TransformComponent> sys::RenderSystem::createTransformComponent()
{
    transformComponents.emplace_back();
    return std::shared_ptr<comp::TransformComponent>(&*transformComponents.end());
}



void sys::RenderSystem::updateSpriteModelMatrix(comp::rend::SpriteComponent *spriteComponent)
{
    auto iter = std::find_if(transformComponents.begin(), transformComponents.end(), [sprite = spriteComponent](auto &transform){
        return transform.isDirty() && transform.getOwnerUUID() == sprite->getOwnerUUID();
    });
    if(iter != transformComponents.end())
    {
        spriteComponent->setTransformMatrix(iter->getTransformMatrix());
    }
}


void sys::RenderSystem::updateViewAndProjectionMatrices(comp::rend::SpriteComponent *spriteComponent)
{
    spriteComponent->setProjectionMatrix(camerasComponents[mainCameraId]->getProjectionMatrix());
    spriteComponent->setViewMatrix(camerasComponents[mainCameraId]->getViewMatrix());
}

void sys::RenderSystem::start()
{
    for(auto& sprite:spritesComponent)
    {
        TaskSystem::addTask(core::threading::TaskPriority::Normal, this,&RenderSystem::updateSpriteModelMatrix,&sprite);
        TaskSystem::addTask(core::threading::TaskPriority::Normal, this,&RenderSystem::updateViewAndProjectionMatrices,&sprite);
        TaskSystem::addTask<comp::rend::RenderComponent>(core::threading::TaskPriority::Normal, &sprite,&comp::rend::SpriteComponent::start);

    }
    for(auto& spriteInstanced:instancedSpritesComponents)
    {
        TaskSystem::addTask<RenderSystem,void,comp::rend::SpriteComponent*>(core::threading::TaskPriority::Normal,this,&RenderSystem::updateViewAndProjectionMatrices,&spriteInstanced);
        TaskSystem::addTask<comp::rend::RenderComponent>(core::threading::TaskPriority::Normal, &spriteInstanced,&comp::rend::SpriteInstancedComponent::start);
    }
}




void sys::RenderSystem::render(float alpha)
{
    for(auto& sprite:spritesComponent)
    {
        TaskSystem::addTask(core::threading::TaskPriority::Normal, this,&RenderSystem::updateSpriteModelMatrix,&sprite);
        TaskSystem::addTask(core::threading::TaskPriority::Normal, this,&RenderSystem::updateViewAndProjectionMatrices,&sprite);
        TaskSystem::addTask<comp::rend::RenderComponent>(core::threading::TaskPriority::Normal, &sprite,&comp::rend::SpriteComponent::update,alpha);
    }
    for(auto& spriteInstanced:instancedSpritesComponents)
    {
        TaskSystem::addTask<RenderSystem,void,comp::rend::SpriteComponent*>(core::threading::TaskPriority::Normal,this,&RenderSystem::updateViewAndProjectionMatrices,&spriteInstanced);
        TaskSystem::addTask<comp::rend::RenderComponent>(core::threading::TaskPriority::Normal, &spriteInstanced,&comp::rend::SpriteInstancedComponent::update,alpha);
    }
}




std::shared_ptr<comp::CameraComponent> sys::RenderSystem::getMainCamera()
{
    HEXEN_ASSERT(mainCameraId < camerasComponents.size() , "Failed to get camera.Wrong main camera id!\n");
    if(!camerasComponents.empty())
    {
        return camerasComponents[mainCameraId];
    }

    return nullptr;
}


template<typename T, std::enable_if_t<std::is_base_of_v<comp::CameraComponent, T>, bool>> void sys::RenderSystem::addCameraComponent(core::i32 viewportWidth, core::i32 viewportHeight,float FOV)
{
    camerasComponents.emplace_back(core::mem::make_shared<T>(viewportWidth,viewportHeight,FOV));
}



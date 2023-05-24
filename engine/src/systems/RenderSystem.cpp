//
// Created by cx9ps3 on 23.05.2023.
//

#include "RenderSystem.h"
#include <algorithm>

std::vector<comp::rend::SpriteComponent> sys::RenderSystem::spritesComponent;
std::vector<comp::rend::SpriteInstancedComponent> sys::RenderSystem::instancedSpritesComponents;
std::vector<comp::TransformComponent> sys::RenderSystem::transformComponents;
std::vector<comp::CameraComponent> sys::RenderSystem::camerasComponents;

sys::RenderSystem::RenderSystem(core::u32 sizeOfVectors)
{
    spritesComponent.reserve(sizeOfVectors);
    instancedSpritesComponents.reserve(sizeOfVectors);
    transformComponents.reserve(sizeOfVectors);
    camerasComponents.reserve(sizeOfVectors);
}

std::shared_ptr<comp::rend::SpriteComponent>
sys::RenderSystem::createSpriteComponent(const std::string &vertexShaderPath,const std::string &fragmentShaderPath)
{
    spritesComponent.emplace_back(vertexShaderPath,fragmentShaderPath);
    return std::shared_ptr<comp::rend::SpriteComponent>(&*spritesComponent.end());
}

std::shared_ptr<comp::rend::SpriteInstancedComponent>
sys::RenderSystem::createSpriteInstancedSprite(const std::string &vertexShaderPath,const std::string &fragmentShaderPath,core::i32 numberOfInstances,glm::mat4 *instancesMatrices)
{
    instancedSpritesComponents.emplace_back(vertexShaderPath,fragmentShaderPath,numberOfInstances,instancesMatrices);
    return std::shared_ptr<comp::rend::SpriteInstancedComponent>(&*instancedSpritesComponents.end());
}

std::shared_ptr<comp::TransformComponent> sys::RenderSystem::createTransformComponent()
{
    transformComponents.emplace_back();
    return std::shared_ptr<comp::TransformComponent>(&*transformComponents.end());
}

std::shared_ptr<comp::CameraComponent>
sys::RenderSystem::createCameraComponent(core::i32 viewportWidth, core::i32 viewportHeight,float FOV)
{
    camerasComponents.emplace_back(viewportWidth,viewportHeight,FOV);
    return std::shared_ptr<comp::CameraComponent>(&*camerasComponents.end());
}

void
sys::RenderSystem::updateSpriteModelMatrix(comp::rend::SpriteComponent &spriteComponent)
{
    auto iter = std::find_if(transformComponents.begin(), transformComponents.end(), [sprite = spriteComponent](auto &transform){
        return transform.isDirty() && transform.getOwnerUUID() == sprite.getOwnerUUID();
    });
    if(iter != transformComponents.end())
    {
        spriteComponent.setTransformMatrix(iter->getTransformMatrix());
    }
}

void
sys::RenderSystem::updateViewAndProjectionMatrices(comp::rend::SpriteComponent *spriteComponent)
{
    for(auto& camera:camerasComponents )
    {
        spriteComponent->setProjectionMatrix(camera.getProjectionMatrix());
        spriteComponent->setViewMatrix(camera.getViewMatrix());
    }
}

void sys::RenderSystem::start()
{
    for(auto& sprite:spritesComponent)
    {
        updateSpriteModelMatrix(sprite);
        updateViewAndProjectionMatrices(&sprite);
        sprite.start();
    }
    for(auto& spriteInstenced:instancedSpritesComponents)
    {
        updateViewAndProjectionMatrices(&spriteInstenced);
        spriteInstenced.start();
    }
}

void sys::RenderSystem::update(float deltaTime)
{
    for(auto& sprite:spritesComponent)
    {
        updateSpriteModelMatrix(sprite);
        updateViewAndProjectionMatrices(&sprite);
        sprite.update(deltaTime);
    }
    for(auto& spriteInstenced:instancedSpritesComponents)
    {
        updateViewAndProjectionMatrices(&spriteInstenced);
        spriteInstenced.update(deltaTime);
    }
}

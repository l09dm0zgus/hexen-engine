//
// Created by cx9ps3 on 28.01.23.
//

#include "SpriteInstancedComponentPool.h"

SpriteInstancedComponentPool::SpriteInstancedComponentPool(int numberOfObjects)
{
    pool = new BaseComponentPool<SpriteInstancedComponent>(numberOfObjects);
    if(pool == nullptr)
    {
        SDL_Log("Failed to allocate memory for SpriteInstancedComponent pool!\n");
        exit(-1);
    }
}

SpriteInstancedComponentPool::~SpriteInstancedComponentPool()
{
    SDL_Log("SpriteInstancedComponent pool deleted!\n");
    delete pool;
    pool = nullptr;
}

SpriteInstancedComponent *SpriteInstancedComponentPool::create(const std::string &vertexShaderPath,const std::string &fragmentShaderPath,int numberOfInstances,glm::mat4 *instancesMatrices)
{
    SpriteInstancedComponent *spriteInstancedComponent = pool->create();
    SDL_Log("Object with UUID %s created!",spriteInstancedComponent->uuid.c_str());
    spriteInstancedComponent->setInstancesMatrices(instancesMatrices);
    spriteInstancedComponent->setNumberOfInstances(numberOfInstances);
    spriteInstancedComponent->create(vertexShaderPath,fragmentShaderPath);
    return spriteInstancedComponent;
}

void SpriteInstancedComponentPool::remove(SpriteInstancedComponent *spriteInstancedComponent)
{

    SDL_Log("Object with UUID %s has been removed!",spriteInstancedComponent->uuid.c_str());
    pool->remove(spriteInstancedComponent);
}


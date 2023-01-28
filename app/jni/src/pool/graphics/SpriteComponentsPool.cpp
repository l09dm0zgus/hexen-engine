//
// Created by cx9ps3 on 28.01.23.
//

#include "SpriteComponentsPool.h"

SpriteComponentsPool::SpriteComponentsPool(int numberOfObjects)
{
    pool = new BaseComponentPool<SpriteComponent>(numberOfObjects);
    if(pool == nullptr)
    {
        SDL_Log("Failed to allocate memory for SpriteComponent pool!\n");
        exit(-1);
    }
}

SpriteComponentsPool::~SpriteComponentsPool()
{
    SDL_Log("Texture pool deleted!\n");
    delete pool;
    pool = nullptr;
}

void SpriteComponentsPool::remove(SpriteComponent *spriteComponent)
{
    SDL_Log("Object with UUID %s has been removed!",spriteComponent->uuid.c_str());
    pool->remove(spriteComponent);
}

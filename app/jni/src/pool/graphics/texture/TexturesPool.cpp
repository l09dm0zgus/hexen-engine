//
// Created by cx9ps3 on 26.01.23.
//

#include "TexturesPool.h"

TexturesPool::TexturesPool(int numberOfObjects)
{
    pool = new BasePool<Texture>(numberOfObjects);
    if(pool == nullptr)
    {
        SDL_Log("Failed to allocate memory for texture pool!\n");
        exit(-1);
    }
}

Texture *TexturesPool::create(const std::string pathToImage, int wrapMode, int filterMode)
{
    Texture *texture = pool->create();
    if(texture == nullptr)
    {
        SDL_Log("Failed to create texture!\n");
        exit(-1);
    }
    texture->create(pathToImage,wrapMode,filterMode);
    return texture;



}
TexturesPool::~TexturesPool()
{
    SDL_Log("Texture pool deleted!\n");
    delete pool;
    pool = nullptr;
}

void TexturesPool::remove(Texture *texture)
{
    auto iterator = std::find_if(pool->getObjects()->begin(),pool->getObjects()->end(),[&texture](Texture t){
        return texture->getId() == t.getId();
    });
    if (iterator != pool->getObjects()->end())
    {
        std::vector<bool> *isUsing = pool->getIsUsing();
        int distance = std::distance(pool->getObjects()->begin(),iterator);
        isUsing->at(distance) = false;
    }
    texture = nullptr;
    pool->remove();
}

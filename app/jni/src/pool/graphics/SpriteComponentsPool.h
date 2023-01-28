//
// Created by cx9ps3 on 28.01.23.
//

#ifndef BATTLEBLAZE_SPRITECOMPONENTSPOOL_H
#define BATTLEBLAZE_SPRITECOMPONENTSPOOL_H
#include "../BaseComponentPool.h"
#include "../../components/graphics/SpriteComponent.h"

class SpriteComponentsPool
{
public:
    SpriteComponentsPool(int numberOfObjects);
    ~SpriteComponentsPool();
    SpriteComponent* create(const std::string &vertexShaderPath , const std::string &fragmentShaderPath);
    void remove(SpriteComponent *spriteComponent);
private:
    BaseComponentPool<SpriteComponent> *pool;
};


#endif //BATTLEBLAZE_SPRITECOMPONENTSPOOL_H

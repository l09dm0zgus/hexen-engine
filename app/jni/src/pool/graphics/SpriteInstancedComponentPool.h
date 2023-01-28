//
// Created by cx9ps3 on 28.01.23.
//

#ifndef BATTLEBLAZE_SPRITEINSTANCEDCOMPONENTPOOL_H
#define BATTLEBLAZE_SPRITEINSTANCEDCOMPONENTPOOL_H
#include "../BaseComponentPool.h"
#include "../../components/graphics/SpriteInstancedComponent.h"

class SpriteInstancedComponentPool
{
public:
    SpriteInstancedComponentPool(int numberOfObjects);
    ~SpriteInstancedComponentPool();
    SpriteInstancedComponent *create(const std::string &vertexShaderPath , const std::string &fragmentShaderPath,int numberOfInstances,glm::mat4 *instancesMatrices);
    void remove(SpriteInstancedComponent * spriteInstancedComponent);
private:
    BaseComponentPool<SpriteInstancedComponent> *pool;

};


#endif //BATTLEBLAZE_SPRITEINSTANCEDCOMPONENTPOOL_H

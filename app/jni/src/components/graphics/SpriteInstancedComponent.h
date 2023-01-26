//
// Created by cx9ps3 on 14.01.23.
//

#ifndef BATTLEBLAZE_SPRITEINSTANCEDCOMPONENT_H
#define BATTLEBLAZE_SPRITEINSTANCEDCOMPONENT_H
#include "SpriteComponent.h"

class SpriteInstancedComponent : public SpriteComponent
{
public:
    void setNumberOfInstances(int numberOfInstances);
    void setInstancesMatrices(glm::mat4 *instancesMatrices);
    void create(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) override;
    void draw() override;
private:
    VertexBufferObject *instancesBuffer{nullptr};
    int numberOfInstances{0};
    glm::mat4 *instancesMatrices;
};


#endif //BATTLEBLAZE_SPRITEINSTANCEDCOMPONENT_H

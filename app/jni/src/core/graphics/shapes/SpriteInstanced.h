//
// Created by cx9ps3 on 14.01.23.
//

#ifndef BATTLEBLAZE_SPRITEINSTANCED_H
#define BATTLEBLAZE_SPRITEINSTANCED_H
#include "Sprite.h"

class SpriteInstanced : public Sprite
{
public:
    SpriteInstanced(const std::string &vertexShaderPath,const std::string &fragmentShaderPath, int numberOfInstances,const glm::mat4 *instancesMatrices);
    void render(const glm::mat4 &projection , const glm::mat4 &view) override;
private:
    VertexBufferObject *instancesBuffer{nullptr};
    int numberOfInstances{0};
};


#endif //BATTLEBLAZE_SPRITEINSTANCED_H

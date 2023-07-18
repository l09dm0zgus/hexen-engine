//
// Created by cx9ps3 on 14.01.23.
//

#pragma once

#include "SpriteComponent.h"
#include "../../core/Types.h"
namespace comp::rend
{
    class SpriteInstancedComponent : public SpriteComponent
    {
    public:
        SpriteInstancedComponent(const std::string &vertexShaderPath , const std::string &fragmentShaderPath,core::i32 numberOfInstances,glm::mat4 *instancesMatrices);
        void draw() noexcept override;
    private:
        core::rend::VertexBufferObject instancesBuffer;
        core::i32 numberOfInstances{0};
        glm::mat4 *instancesMatrices{nullptr};
    };

}

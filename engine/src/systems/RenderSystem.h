//
// Created by cx9ps3 on 23.05.2023.
//

#pragma once

#include "../core/Types.h"
#include "../components/graphics/SpriteComponent.h"
#include "../components/graphics/SpriteInstancedComponent.h"
#include "../components/transform/TransformComponent.h"
#include "../components/camera/CameraComponent.h"
#include "IRenderSystem.h"
#include <vector>
#include <memory>

namespace sys
{
    class RenderSystem : public IRenderSystem
    {
    public:
        explicit RenderSystem(core::u32 sizeOfVectors);
        static std::shared_ptr<comp::rend::SpriteComponent> createSpriteComponent(const std::string &vertexShaderPath , const std::string &fragmentShaderPath);
        static std::shared_ptr<comp::rend::SpriteInstancedComponent> createSpriteInstancedSprite(const std::string &vertexShaderPath , const std::string &fragmentShaderPath,core::i32 numberOfInstances,glm::mat4 *instancesMatrices);
        static std::shared_ptr<comp::TransformComponent> createTransformComponent();
        static std::shared_ptr<comp::CameraComponent> createCameraComponent(core::i32 viewportWidth, core::i32 viewportHeight, float FOV);
        void start() override;
        void render(float alpha) override;
    private:
        static std::vector<comp::rend::SpriteComponent> spritesComponent;
        static std::vector<comp::rend::SpriteInstancedComponent> instancedSpritesComponents;
        static std::vector<comp::TransformComponent> transformComponents;
        static std::vector<comp::CameraComponent> camerasComponents;
        void updateSpriteModelMatrix(comp::rend::SpriteComponent &spriteComponent);
        void updateViewAndProjectionMatrices(comp::rend::SpriteComponent *spriteComponent);
    };
}


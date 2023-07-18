//
// Created by cx9ps3 on 10.01.23.
//

#pragma once


#include <glm/glm.hpp>
#include "../../core/Types.h"
#include "../Component.h"
namespace comp
{
    class CameraComponent : public Component
    {
    public:
        CameraComponent(core::i32 viewportWidth, core::i32 viewportHeight, float FOV);
        template<class T>void setPosition(T&& newPosition) noexcept;
        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();
        void start() override;
        void update(float deltaTime) override;
    private:
        glm::vec3 position{1.0f};
        glm::mat4 view{1.0f};
        glm::mat4 projection{1.0f};
        glm::vec3 cameraTarget{0.0f,0.0f,-1.0f};
        glm::vec3 cameraUp{0.0f,1.0f,0.0f};
        void updateViewMatrix();
    };
}


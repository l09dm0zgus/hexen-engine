//
// Created by cx9ps3 on 19.01.23.
//

#ifndef BATTLEBLAZE_RENDERCOMPONENT_H
#define BATTLEBLAZE_RENDERCOMPONENT_H
#include "../IComponent.h"
#include "../../core/camera/Camera.h"
#include <glm/glm.hpp>
#include <iostream>

namespace comp::rend
{
    class RenderComponent : public IComponent
    {
    public:
        ~RenderComponent() = default;
        RenderComponent(const RenderComponent& renderComponent) = default;
        RenderComponent(RenderComponent &&) = default;
        RenderComponent& operator=(RenderComponent&& renderComponent) = default;
        RenderComponent& operator=(const RenderComponent &renderComponent) = default;

        template<class T> void setProjectionMatrix(T&& newProjection) noexcept;
        template<class T> void setViewMatrix(T &&newView) noexcept;
        template<class T> void setTransformMatrix(T&& newTransform) noexcept;

        glm::mat4 getProjectionMatrix() const noexcept;
        glm::mat4 getViewMatrix() const noexcept;
        glm::mat4 getTransformMatrix() const noexcept;

        virtual void start() override;
        virtual void update(float deltaTime) override;
        virtual void draw() = 0;

    private:
        glm::mat4 projection{1.0f};
        glm::mat4 view{1.0f};
        glm::mat4 transform{1.0f};
    };
}



#endif //BATTLEBLAZE_RENDERCOMPONENT_H

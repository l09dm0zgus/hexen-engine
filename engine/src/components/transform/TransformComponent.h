//
// Created by cx9ps3 on 09.01.23.
//

#ifndef BATTLEBLAZE_TRANSFORMCOMPONENT_H
#define BATTLEBLAZE_TRANSFORMCOMPONENT_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Component.h"

#define GLM_SWIZZLE

namespace comp
{
    class TransformComponent: public comp::Component
    {
    public:
        TransformComponent() = default;
        ~TransformComponent() = default;
        TransformComponent(float layer);
        TransformComponent(const glm::vec2 &newPosition);
        TransformComponent(const glm::mat4 &newTransform);
        TransformComponent(const TransformComponent &transformComponent);
        TransformComponent(TransformComponent &&transformComponent) noexcept;
        TransformComponent(const glm::vec2 &newPosition,const glm::vec2 &newRotation);
        TransformComponent(const glm::vec2 &newPosition,const glm::vec2 &newRotation,const glm::vec2 &newScale);
        TransformComponent(const glm::vec2 &newPosition,const glm::vec2 &newRotation,const glm::vec2 &newScale,float layer);
        TransformComponent& operator=(const TransformComponent &transformComponent);
        TransformComponent& operator=(TransformComponent &&transformComponent) noexcept;

        template<class T>
        void setPosition(T&& newPosition) noexcept;
        template<class T>
        void setRotation(T&& newRotation) noexcept;
        template<class T>
        void setScale(T&& newScale) noexcept;
        void setLayer(float layer);

        float getLayer() const noexcept;
        glm::vec2 getScale() const noexcept;
        glm::vec2 getPosition() const noexcept;
        glm::vec2 getRotation() const noexcept;
        void updateTransformMatrix();
        template<class T>void updateTransformMatrix(T &&parentTransform)
        {
            updateTransformMatrix();
            transformMatrix = transformMatrix * std::forward<T>(parentTransform);
        }
        glm::mat4 getTransformMatrix() const noexcept;
        bool isDirty() const noexcept;


        void start() override;
        void update(float  deltaTime) override;
    private:
        void move(TransformComponent &&transformComponent) noexcept;
        void copy(const TransformComponent &transformComponent);
        glm::mat4 rotate(const glm::mat4 &rotationMatrix,const glm::vec2 &rotation) const;
        glm::mat4 transformMatrix{1.0f};
        glm::vec2 position{0.0f};
        glm::vec2 rotation{0.0f};
        glm::vec2 scale{1.0f};
        glm::vec3 zCoordinates{0.0f};
        float layer{0.0f};
        const float layerDivider{10.0f};
        bool bIsDirty{true};
    };

}

#endif //BATTLEBLAZE_TRANSFORMCOMPONENT_H

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

        /**
        * @class comp::CameraComponent
        * @brief Represents a camera component used in a game engine.
        *
        * This class encapsulates the properties and behaviors of a camera used for rendering
        * a viewport in a game engine. It provides methods for setting the viewport dimensions,
        * field of view, and other camera-related functionalities.
        */

        CameraComponent(core::i32 viewportWidth, core::i32 viewportHeight, float FOV);

        template<class T>void setPosition(T&& newPosition) noexcept
        {
            position = std::forward<T>(newPosition);
            updateViewMatrix();
        }

        /**
        * @brief Get the view matrix of the camera.
        *
        * This function returns the view matrix of the camera component. The view matrix
        * represents the transformation from world space to view space, which is necessary
        * for rendering the scene from the perspective of the camera.
        *
        * @return The view matrix of the camera.
        */


        glm::mat4 getViewMatrix();

        /**
        * @brief Retrieves the projection matrix of the camera component.
        *
        * This method returns the 4x4 projection matrix, which is used to transform
        * three-dimensional coordinates into two-dimensional space during the rendering process.
        *
        * The returned projection matrix is determined by the camera settings, such as field of view,
        * aspect ratio, near and far clipping planes.
        *
        * @return The 4x4 projection matrix representing the camera component's projection transformation.
        */

        glm::mat4 getProjectionMatrix();

        /**
        * @brief Starts the camera component.
        *
        * This function starts the camera component by initializing the necessary resources and setting up the camera.
        * It assumes that the necessary dependencies have been resolved before calling this function.
        *
        */

        void start() override;

        /**
        * @brief Updates the CameraComponent based on the elapsed time.
        *
        * This function updates the CameraComponent based on the elapsed time.
        * It adjusts the camera's position, orientation, or any other relevant properties.
        *
        * @param deltaTime The elapsed time since the last update, in seconds.
        *
        */


        void update(float deltaTime) override;

        /**
        * @brief Moves the camera based on the given value.
        *
        * This function translates the camera's position based on the specified value.
        * A positive value moves the camera forward, while a negative value moves the camera backward.
        *
        * @param value The value to move the camera by.
        *
        */


        void move(float value);

        /**
        * @brief Adjusts the zoom level of the camera.
        *
        * This function allows adjusting the zoom level of the camera by applying a zoom factor.
        *
        * @param value The zoom factor to be applied. A value of 1.0 represents no zoom,
        *              values greater than 0 represent a zoom-in effect,
        *              values smaller than 0 represent a zoom-out effect.
        *
        * @note The zoom value can be negative to invert the zoom direction.
        *
        */

        void zoom(float value);

        /**
        * @brief Rotates the camera by the specified yaw and pitch angles.
        *
        * This method rotates the camera by the specified yaw and pitch angles. The yaw angle
        * represents the rotation around the vertical axis, while the pitch angle represents
        * the rotation around the horizontal axis.
        *
        * @param yawAngle The yaw angle in degrees.
        * @param pitchAngle The pitch angle in degrees.
        *
        */

        void rotate(float yawAngle = 0.0f, float pitchAngle = 0.0f);
    private:
        float deltaTime{0};
        glm::vec3 position{1.0f};
        glm::mat4 view{1.0f};
        glm::mat4 projection{1.0f};
        glm::vec3 cameraTarget{0.0f,0.0f,-1.0f};
        glm::vec3 cameraUp{0.0f,1.0f,0.0f};

        /**
        * @brief Updates the view matrix of the camera component.
        *
        * This function calculates and updates the view matrix of the camera component
        * based on its current position, target and up vector. The view matrix is used to
        * transform the world coordinates to camera/view space.
        *
        */

        void updateViewMatrix();
    };
}


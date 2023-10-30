//
// Created by cx9ps3 on 10.01.23.
//

#pragma once


#include "../../core/Types.hpp"
#include "../Component.hpp"
#include <glm/glm.hpp>
namespace hexen::engine::components::graphics
{
	/**
    * @class CameraComponent
    * @brief Represents a camera component used in a game engine.
    *
    * This class encapsulates the properties and behaviors of a camera used for rendering
    * a viewport in a game engine. It provides methods for setting the viewport dimensions,
    * field of view, and other camera-related functionalities.
    */

	class CameraComponent : public Component
	{
	public:

		CameraComponent() = default;

		/**
 		* @constructor CameraComponent::CameraComponent
 		* @brief Constructs a new CameraComponent object.
 		*
 		* @param viewportWidth The width of the viewport.
 		* @param viewportHeight The height of the viewport.
 		* @param FOV The field of view of the camera.
 		*
 		* @details The constructor initializes the CameraComponent with the given parameters
 		* and updates the projection and view matrices.
 		*/

		CameraComponent(core::i32 viewportWidth, core::i32 viewportHeight, float FOV);

		/**
        * @fn setPosition
        * @brief Sets the position of the object.
        * @tparam T The type of the new position.
        * @param newPosition The new position to set.
        *
        * @note This function sets the position of the object.
        *       It takes a new position as a parameter and assigns it to the object's position.
        *       The position is passed as rvalue reference, allowing for efficient move semantics.
        *       The function is marked as noexcept, indicating that it does not throw any exceptions.
        */

		template<class T>
		void setPosition(T &&newPosition) noexcept
		{
			HEXEN_ADD_TO_PROFILE();
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

		[[nodiscard]] glm::mat4 getViewMatrix();

		/**
        * @brief Updates the projection matrix of the camera component.
        *
        * This function is used to update the projection matrix of the camera component based on the new screen dimensions.
        *
        * @param newWindowWidth The new width of the screen.
        * @param newWindowHeight The new height of the screen.
        *
        *
        * @note Make sure to call this function whenever the screen dimensions change to ensure accurate rendering.
        */

		void updateProjectionMatrix(core::u32 newWindowWidth, core::u32 newWindowHeight);

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

		[[nodiscard]] glm::mat4 getProjectionMatrix();


		/**
        * Sets the setYaw angle of the camera component.
        *
        * The setYaw angle determines the horizontal rotation of the camera
        * around the vertical axis. A positive setYaw angle rotates the camera
        * to the right, while a negative setYaw angle rotates it to the left.
        *
        * @param yawAngle The setYaw angle to set, in degrees.
        */

		void setYaw(float yawAngle);

		/**
        * Changes the pitch angle of the camera.
        *
        * This function allows you to change the pitch angle of the camera.
        *
        * @param pitchAngle The new pitch angle to set, in degrees.
        */

		void setPitch(float pitchAngle);

		/**
 		* @brief Get the yaw value of the camera.
 		*
 		* This function returns the yaw value of the camera. The yaw represents
 		* the rotation around the vertical y-axis.
 		*
 		* @return The yaw value of the camera.
 		*/

		[[nodiscard]] float getYaw() const noexcept;

		/**
 		* @brief Get the pitch angle of the camera.
 		*
 		* This function returns the pitch angle of the camera component. The pitch angle
 		* represents the vertical rotation of the camera around its local x-axis.
 		*
 		* @return The pitch angle of the camera in degrees.
 		*
	 	* @note This function is const and noexcept, meaning it does not throw any exceptions
 		*       and does not modify the internal state of the camera component.
 		*/

		[[nodiscard]] float getPitch() const noexcept;

		float deltaTime{0};

	private:
		/**
         * @brief View Matrix.
         */

		glm::mat4 view {1.0f};

		/**
         * @brief Projection Matrix.
         */

		glm::mat4 projection {1.0f};

		/**
         * @brief Default Up direction in world space.
         */

		glm::vec3 worldUp {0.0f, 1.0f, 0.0f};

		/**
         * @brief Field of View Angle.
         */

		float FOV {90.0f};

		/**
         * @brief Current Yaw Angle.
         */

		float currentYawAngle {-45.0};

		/**
         * @brief Current Pitch Angle.
         */

		float currentPitchAngle {270.0f};

	protected:
		/**
         * @brief Up direction in camera space.
         */

		glm::vec3 cameraUp {1.0f};

		/**
         * @brief Right direction in camera space.
         */

		glm::vec3 cameraRight {1.0f};

		/**
         * @brief The point that the camera is looking at.
         */

		glm::vec3 cameraTarget {0.0f, 0.0f, -1.0f};

		/**
         * @brief Position of the camera in world space.
         */

		glm::vec3 position {5.0f, 15.0f, 5.0f};

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
}// namespace hexen::engine::components::graphics

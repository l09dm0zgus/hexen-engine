//
// Created by cx9ps3 on 18.09.2023.
//

#pragma once
#include <components/camera/CameraComponent.hpp>

namespace hexen::editor::components::graphics
{
	class EditorCameraComponent : public engine::components::graphics::CameraComponent
	{
	private:
		float velocity {100.f};
		float deltaTime {0};

	public:
		/**
        * Moves the camera component forward by the specified value.
        *
        * @param value The distance to move the camera forward.
        */

		void moveForward(float value);

		/**
        * Moves the camera component to the right by the specified value.
        *
        * @param value The amount to move the camera to the right.
        */


		void moveRight(float value);

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
        * @param newDeltaTime The elapsed time since the last update, in seconds.
        *
        */


		void update(float newDeltaTime) override;
	};
}// namespace hexen::editor::components::graphics

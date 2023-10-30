//
// Created by cx9ps3 on 18.09.2023.
//

#pragma once
#include <components/camera/CameraComponent.hpp>

namespace hexen::editor::components::graphics
{

	/**
     * @class hexen::editor::components::EditorCameraComponent
     * @brief Represents a camera component used in editor.
     *
     * This class encapsulates the properties and behaviors of a camera used for rendering
     * a viewport in a game engine. It provides methods for setting the viewport dimensions,
     * field of view, and other camera-related functionalities.
     */

	class EditorCameraComponent : public engine::components::graphics::CameraComponent
	{
	private:
		float velocity {100.f};

	public:

		/**
 		* @brief Constructor for EditorCameraComponent
 		*
 		* @param viewportWidth The width of the viewport in pixels
 		* @param viewportHeight The height of the viewport in pixels
 		* @param FOV The field of view for the camera in degrees
 		*/

		EditorCameraComponent(engine::core::i32 viewportWidth, engine::core::i32 viewportHeight, float FOV);

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

	};
}// namespace hexen::editor::components::graphics

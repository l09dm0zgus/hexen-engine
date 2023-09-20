//
// Created by cx9ps3 on 18.09.2023.
//

#include "EditorCameraComponent.hpp"
#include <systems/InputHelper.hpp>
void hexen::editor::components::graphics::EditorCameraComponent::moveForward(float value)
{
	position += (value * deltaTime * velocity) * cameraUp;
	updateViewMatrix();
}

void hexen::editor::components::graphics::EditorCameraComponent::moveRight(float value)
{
	position += (value * deltaTime * velocity) * cameraRight;
	updateViewMatrix();
}

void hexen::editor::components::graphics::EditorCameraComponent::zoom(float value)
{
	position += cameraTarget * (value * deltaTime * velocity);
	updateViewMatrix();
}
void hexen::editor::components::graphics::EditorCameraComponent::start()
{
	CameraComponent::start();

}
void hexen::editor::components::graphics::EditorCameraComponent::update(float newDeltaTime)
{
	CameraComponent::update(newDeltaTime);
	deltaTime = newDeltaTime;
}
hexen::editor::components::graphics::EditorCameraComponent::EditorCameraComponent(hexen::engine::core::i32 viewportWidth, engine::core::i32 viewportHeight, float FOV) : CameraComponent(viewportWidth, viewportHeight, FOV)
{
	engine::input::InputHelper::addNewAxisMapping("MoveForward", 1.0f, static_cast<engine::core::u32>(engine::core::input::Keyboard::Key::W));
	engine::input::InputHelper::addNewAxisMapping("MoveForward", -1.0f, static_cast<engine::core::u32>(engine::core::input::Keyboard::Key::S));
	engine::input::InputHelper::addNewAxisMapping("MoveRight", 1.0f, static_cast<engine::core::u32>(engine::core::input::Keyboard::Key::D));
	engine::input::InputHelper::addNewAxisMapping("MoveRight", -1.0f, static_cast<engine::core::u32>(engine::core::input::Keyboard::Key::A));
	engine::input::InputHelper::addNewAxisMapping("Zoom", 1.0f, static_cast<engine::core::u32>(engine::core::input::Keyboard::Key::Q));
	engine::input::InputHelper::addNewAxisMapping("Zoom", -1.0f, static_cast<engine::core::u32>(engine::core::input::Keyboard::Key::E));

	engine::input::InputHelper::bindAxis("MoveForward", this,&EditorCameraComponent::moveForward);

	engine::input::InputHelper::bindAxis("MoveRight", this,&EditorCameraComponent::moveRight);

	engine::input::InputHelper::bindAxis("Zoom", this,&EditorCameraComponent::zoom);
}
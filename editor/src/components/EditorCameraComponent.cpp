//
// Created by cx9ps3 on 18.09.2023.
//

#include "EditorCameraComponent.hpp"
#include <uuid/uuid.hpp>
#include <systems/InputHelper.hpp>

hexen::engine::core::u32 hexen::editor::components::graphics::EditorCameraComponent::countOfInstances = 0;

void hexen::editor::components::graphics::EditorCameraComponent::moveUp(float value)
{
	HEXEN_ADD_TO_PROFILE()
	if (cameraProjection == engine::components::graphics::CameraProjection::PERSPECTIVE)
	{
		position += (value * deltaTime * velocity) * cameraUp;
	}
	else
	{
		position += (value * deltaTime * velocity) * -cameraUp;
	}

	updateViewMatrix();
}

void hexen::editor::components::graphics::EditorCameraComponent::moveRight(float value)
{
	HEXEN_ADD_TO_PROFILE()
	position += (value * deltaTime * velocity) * cameraRight;
	updateViewMatrix();
}

void hexen::editor::components::graphics::EditorCameraComponent::zoom(float value)
{
	HEXEN_ADD_TO_PROFILE()
	if (cameraProjection == engine::components::graphics::CameraProjection::PERSPECTIVE)
	{
		position += cameraTarget * (value * deltaTime * velocity);
	}
	else
	{
		orthoZoom += (value * deltaTime * (1.0f / velocity));
		updateProjectionMatrix();
	}

	updateViewMatrix();
}

hexen::editor::components::graphics::EditorCameraComponent::EditorCameraComponent(hexen::engine::core::i32 viewportWidth, engine::core::i32 viewportHeight, float FOV) : CameraComponent(viewportWidth, viewportHeight, FOV)
{
	HEXEN_ADD_TO_PROFILE()
	countOfInstances++;
}

void hexen::editor::components::graphics::EditorCameraComponent::enableInput()
{
	engine::input::InputHelper::enableInputForPlayer(countOfInstances);
}

void hexen::editor::components::graphics::EditorCameraComponent::setInputMappings()
{
	engine::input::InputHelper::addNewAxisMapping("MoveForward", 1.0f, static_cast<engine::core::u32>(engine::core::input::Keyboard::Key::W),countOfInstances);
	engine::input::InputHelper::addNewAxisMapping("MoveForward", -1.0f, static_cast<engine::core::u32>(engine::core::input::Keyboard::Key::S), countOfInstances);
	engine::input::InputHelper::addNewAxisMapping("MoveRight", 1.0f, static_cast<engine::core::u32>(engine::core::input::Keyboard::Key::D), countOfInstances);
	engine::input::InputHelper::addNewAxisMapping("MoveRight", -1.0f, static_cast<engine::core::u32>(engine::core::input::Keyboard::Key::A), countOfInstances);
	engine::input::InputHelper::addNewAxisMapping("Zoom", 1.0f, static_cast<engine::core::u32>(engine::core::input::Keyboard::Key::Q), countOfInstances);
	engine::input::InputHelper::addNewAxisMapping("Zoom", -1.0f, static_cast<engine::core::u32>(engine::core::input::Keyboard::Key::E), countOfInstances);

	engine::input::InputHelper::bindAxis("MoveForward", this, &EditorCameraComponent::moveUp, true, countOfInstances);

	engine::input::InputHelper::bindAxis("MoveRight", this, &EditorCameraComponent::moveRight, true, countOfInstances);

	engine::input::InputHelper::bindAxis("Zoom", this, &EditorCameraComponent::zoom, true, countOfInstances);
}

void hexen::editor::components::graphics::EditorCameraComponent::disableInput()
{
	engine::input::InputHelper::disableInputForPlayer(countOfInstances);
}

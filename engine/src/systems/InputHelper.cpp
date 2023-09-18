//
// Created by cx9ps3 on 17.09.2023.
//

#include "InputHelper.hpp"
#include "SystemsManager.hpp"


void hexen::engine::input::InputHelper::bindAction(const std::string &name, const std::function<void()> &actionCallback, bool enableForMultiplePLayers)
{
	getInputSystem()->bindAction(name, actionCallback, enableForMultiplePLayers);
}

std::shared_ptr<hexen::engine::systems::InputSystem> hexen::engine::input::InputHelper::getInputSystem()
{
	auto manager = systems::SystemsManager::getCurrentSystemManager();
	HEXEN_ASSERT(manager != nullptr, "SystemsManager is nullptr");

	auto inputSystem = manager->getInputSystem();
	HEXEN_ASSERT(inputSystem != nullptr, "InputSystem is nullptr");

	return inputSystem;
}

void hexen::engine::input::InputHelper::bindAxis(const std::string &name, const std::function<void(float)> &axisCallback, bool enableForMultiplePLayers)
{
	getInputSystem()->bindAxis(name, axisCallback, enableForMultiplePLayers);
}

void hexen::engine::input::InputHelper::saveMappings()
{
	getInputSystem()->saveMappings();
}

void hexen::engine::input::InputHelper::addNewAxisMapping(const std::string &name, float value, hexen::engine::core::u32 sdlKey, hexen::engine::core::u8 playerId)
{
	getInputSystem()->addNewAxisMapping(name, value, sdlKey, playerId);
}

void hexen::engine::input::InputHelper::addNewAxisMapping(const hexen::engine::systems::InputSystem::AxisMapping &axisMapping)
{
	getInputSystem()->addNewAxisMapping(axisMapping);
}

void hexen::engine::input::InputHelper::addNewActionMapping(const std::string &name, hexen::engine::core::u32 sdlKey, hexen::engine::core::u8 playerId)
{
	getInputSystem()->addNewActionMapping(name, sdlKey, playerId);
}

void hexen::engine::input::InputHelper::addNewActionMapping(const hexen::engine::systems::InputSystem::ActionMapping &actionMapping)
{
	getInputSystem()->addNewActionMapping(actionMapping);
}

void hexen::engine::input::InputHelper::changeMapping(const std::string &name, hexen::engine::core::u32 newKey)
{
	getInputSystem()->changeMapping(name, newKey);
}

bool hexen::engine::input::InputHelper::isButtonPressed(hexen::engine::core::input::Keyboard::Key key)
{
	return getInputSystem()->keyboard->isKeyPressed(key);
}

bool hexen::engine::input::InputHelper::isButtonPressed(hexen::engine::core::input::Mouse::Button button)
{
	return getInputSystem()->mouse->isButtonPressed(button);
}

bool hexen::engine::input::InputHelper::isButtonReleased(hexen::engine::core::input::Mouse::Button button)
{
	return getInputSystem()->mouse->isButtonReleased(button);
}

bool hexen::engine::input::InputHelper::isButtonPressed(hexen::engine::core::input::Gamepad::Button button)
{
	if (!getInputSystem()->gamepads.empty())
	{
		return getInputSystem()->gamepads[0]->isButtonPressed(button);
	}
	return false;
}

bool hexen::engine::input::InputHelper::isButtonReleased(hexen::engine::core::input::Gamepad::Button button)
{
	if (!getInputSystem()->gamepads.empty())
	{
		return getInputSystem()->gamepads[0]->isButtonReleased(button);
	}
	return false;
}

glm::vec2 hexen::engine::input::InputHelper::getCursorPosition() noexcept
{
	return getInputSystem()->mouse->getPosition();
}

glm::vec2 hexen::engine::input::InputHelper::getMouseLastPressedButtonPosition() noexcept
{
	return getInputSystem()->mouse->getLastPressedButtonPosition();
}

glm::vec2 hexen::engine::input::InputHelper::getMouseLastReleasedButtonPosition() noexcept
{
	return getInputSystem()->mouse->getLastReleasedButtonPosition();
}

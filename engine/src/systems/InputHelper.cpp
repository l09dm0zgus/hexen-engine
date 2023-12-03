//
// Created by cx9ps3 on 17.09.2023.
//

#include "InputHelper.hpp"
#include "SystemsManager.hpp"

void hexen::engine::input::InputHelper::bindAction(const std::string &name, const std::function<void()> &actionCallback, bool enableForMultiplePLayers)
{
	HEXEN_ADD_TO_PROFILE();
	getInputSystem()->bindAction(name, actionCallback, enableForMultiplePLayers);
}

std::shared_ptr<hexen::engine::systems::InputSystem> hexen::engine::input::InputHelper::getInputSystem()
{
	HEXEN_ADD_TO_PROFILE();
	auto manager = systems::SystemsManager::getCurrentSystemManager();
	HEXEN_ASSERT(manager != nullptr, "SystemsManager is nullptr");

	auto inputSystem = manager->getInputSystem();
	HEXEN_ASSERT(inputSystem != nullptr, "InputSystem is nullptr");

	return inputSystem;
}

void hexen::engine::input::InputHelper::bindAxis(const std::string &name, const std::function<void(float)> &axisCallback, bool enableForMultiplePLayers)
{
	HEXEN_ADD_TO_PROFILE();
	getInputSystem()->bindAxis(name, axisCallback, enableForMultiplePLayers);
}

void hexen::engine::input::InputHelper::saveMappings()
{
	HEXEN_ADD_TO_PROFILE();
	getInputSystem()->saveMappings();
}

void hexen::engine::input::InputHelper::addNewAxisMapping(const std::string &name, float value, hexen::engine::core::u32 sdlKey, hexen::engine::core::u8 playerId)
{
	HEXEN_ADD_TO_PROFILE();
	getInputSystem()->addNewAxisMapping(name, value, sdlKey, playerId);
}

void hexen::engine::input::InputHelper::addNewAxisMapping(const hexen::engine::systems::InputSystem::AxisMapping &axisMapping)
{
	HEXEN_ADD_TO_PROFILE();
	getInputSystem()->addNewAxisMapping(axisMapping);
}

void hexen::engine::input::InputHelper::addNewActionMapping(const std::string &name, hexen::engine::core::u32 sdlKey, hexen::engine::core::u8 playerId)
{
	HEXEN_ADD_TO_PROFILE();
	getInputSystem()->addNewActionMapping(name, sdlKey, playerId);
}

void hexen::engine::input::InputHelper::addNewActionMapping(const hexen::engine::systems::InputSystem::ActionMapping &actionMapping)
{
	HEXEN_ADD_TO_PROFILE();
	getInputSystem()->addNewActionMapping(actionMapping);
}

void hexen::engine::input::InputHelper::changeMapping(const std::string &name, hexen::engine::core::u32 newKey)
{
	HEXEN_ADD_TO_PROFILE();
	getInputSystem()->changeMapping(name, newKey);
}

bool hexen::engine::input::InputHelper::isButtonPressed(hexen::engine::core::input::Keyboard::Key key)
{
	return getInputSystem()->keyboard->isKeyPressed(key);
}

bool hexen::engine::input::InputHelper::isButtonPressed(hexen::engine::core::input::Mouse::Button button)
{
	HEXEN_ADD_TO_PROFILE();
	return getInputSystem()->mouse->isButtonPressed(button);
}

bool hexen::engine::input::InputHelper::isButtonReleased(hexen::engine::core::input::Mouse::Button button)
{
	HEXEN_ADD_TO_PROFILE();
	return getInputSystem()->mouse->isButtonReleased(button);
}

bool hexen::engine::input::InputHelper::isButtonPressed(hexen::engine::core::input::Gamepad::Button button)
{
	HEXEN_ADD_TO_PROFILE();
	if (!getInputSystem()->gamepads.empty())
	{
		return getInputSystem()->gamepads[0]->isButtonPressed(button);
	}
	return false;
}

bool hexen::engine::input::InputHelper::isButtonReleased(hexen::engine::core::input::Gamepad::Button button)
{
	HEXEN_ADD_TO_PROFILE();
	if (!getInputSystem()->gamepads.empty())
	{
		return getInputSystem()->gamepads[0]->isButtonReleased(button);
	}
	return false;
}

glm::vec2 hexen::engine::input::InputHelper::getCursorPosition() noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return getInputSystem()->mouse->getPosition();
}

glm::vec2 hexen::engine::input::InputHelper::getMouseLastPressedButtonPosition() noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return getInputSystem()->mouse->getLastPressedButtonPosition();
}

glm::vec2 hexen::engine::input::InputHelper::getMouseLastReleasedButtonPosition() noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return getInputSystem()->mouse->getLastReleasedButtonPosition();
}

void hexen::engine::input::InputHelper::enableInputForPlayer(hexen::engine::core::u32 playerID)
{
	HEXEN_ADD_TO_PROFILE();
	getInputSystem()->enableInputByPlayerID(playerID, true);
}

void hexen::engine::input::InputHelper::disableInputForPlayer(hexen::engine::core::u32 playerID)
{
	HEXEN_ADD_TO_PROFILE();
	getInputSystem()->enableInputByPlayerID(playerID, false);
}

std::shared_ptr<hexen::engine::systems::InputSystem> hexen::engine::input::InputHelper::createInputSystem()
{
	HEXEN_ADD_TO_PROFILE();
	return core::memory::make_shared<systems::InputSystem>();
}

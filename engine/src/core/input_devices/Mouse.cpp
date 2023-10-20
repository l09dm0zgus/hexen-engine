//
// Created by cx9ps3 on 03.09.2023.
//

#include "Mouse.hpp"


bool hexen::engine::core::input::Mouse::processInput(const SDL_Event &event)
{
	HEXEN_ADD_TO_PROFILE();
	auto isMouseEvent = false;
	isMouseWheelMovingOnX = false;
	isMouseWheelMovingOnY = false;
	isMouseMovingOnX = false;
	isMouseMovingOnY = false;

	switch (event.type)
	{
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
		case SDL_EVENT_MOUSE_BUTTON_UP:
			currentButton = event.button.button;
			lastPressedButtonPosition = glm::vec2(event.button.x, event.button.y);
			isMouseEvent = true;
			break;
		case SDL_EVENT_MOUSE_MOTION:

			isMouseMovingOnX = event.motion.x != position.x;
			isMouseMovingOnY = event.motion.y != position.y;
			position = glm::vec2(event.motion.x, event.motion.y);
			isMouseEvent = true;
			break;
		case SDL_EVENT_MOUSE_WHEEL:

			isMouseWheelMovingOnX = event.wheel.x != wheelPosition.x;
			isMouseWheelMovingOnY = event.wheel.y != wheelPosition.y;
			wheelPosition = glm::vec2(event.wheel.x, event.wheel.y);
			isMouseEvent = true;
			break;
	}
	return isMouseEvent;
}

glm::vec2 hexen::engine::core::input::Mouse::getPosition() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return position;
}

glm::vec2 hexen::engine::core::input::Mouse::getLastPressedButtonPosition() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return lastPressedButtonPosition;
}

glm::vec2 hexen::engine::core::input::Mouse::getLastReleasedButtonPosition() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return lastReleasedButtonPosition;
}

bool hexen::engine::core::input::Mouse::isButtonPressed(hexen::engine::core::input::Mouse::Button button) const
{
	HEXEN_ADD_TO_PROFILE();
	return static_cast<core::u8>(button) == currentButton;
}

bool hexen::engine::core::input::Mouse::isButtonReleased(hexen::engine::core::input::Mouse::Button button) const
{
	HEXEN_ADD_TO_PROFILE();
	return static_cast<core::u8>(button) == currentButton;
}

glm::vec2 hexen::engine::core::input::Mouse::getWheelPosition() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return wheelPosition;
}

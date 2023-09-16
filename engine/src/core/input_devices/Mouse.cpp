//
// Created by cx9ps3 on 03.09.2023.
//

#include "Mouse.hpp"
#include "../Types.hpp"

void hexen::engine::core::input::Mouse::processInput(const SDL_Event &event)
{
    switch (event.type)
    {
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case  SDL_EVENT_MOUSE_BUTTON_UP:
            currentButton = event.button.button;
            lastPressedButtonPosition = glm::vec2(event.button.x,event.button.y);
            break;
        case SDL_EVENT_MOUSE_MOTION:
            position = glm::vec2(event.motion.x,event.motion.y);
            break;
        case SDL_EVENT_MOUSE_WHEEL:
            wheelPosition = glm::vec2(event.wheel.x,event.wheel.y);
            break;
    }
}

glm::vec2 hexen::engine::core::input::Mouse::getPosition() const noexcept
{
    return position;
}

glm::vec2 hexen::engine::core::input::Mouse::getLastPressedButtonPosition() const noexcept
{
    return lastPressedButtonPosition;
}

glm::vec2 hexen::engine::core::input::Mouse::getLastReleasedButtonPosition() const noexcept
{
    return lastReleasedButtonPosition;
}

bool hexen::engine::core::input::Mouse::isButtonPressed(hexen::engine::core::input::Mouse::Button button) const
{
    return static_cast<core::u8>(button) == currentButton;
}

bool hexen::engine::core::input::Mouse::isButtonReleased(hexen::engine::core::input::Mouse::Button button) const
{
    return static_cast<core::u8>(button) == currentButton;
}


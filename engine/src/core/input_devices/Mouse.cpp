//
// Created by cx9ps3 on 03.09.2023.
//

#include "Mouse.hpp"

void hexen::engine::core::input::Mouse::processInput(const SDL_Event &event)
{
    switch (event.type)
    {
        case SDL_EVENT_MOUSE_BUTTON_DOWN:

            bIsLeftButtonPressed = event.button.button == SDL_BUTTON_LEFT;
            bIsRightButtonPressed = event.button.button == SDL_BUTTON_RIGHT;
            bIsMiddleButtonPressed = event.button.button == SDL_BUTTON_MIDDLE;
            bIsX1ButtonPressed = event.button.button == SDL_BUTTON_X1;
            bIsX2ButtonPressed = event.button.button == SDL_BUTTON_X2;

            bIsLeftButtonReleased = !bIsLeftButtonPressed;
            bIsRightButtonReleased = !bIsRightButtonPressed;
            bIsMiddleButtonReleased = !bIsMiddleButtonPressed;
            bIsX1ButtonReleased = !bIsX1ButtonPressed;
            bIsX2ButtonReleased = !bIsX2ButtonPressed;

            if(bIsLeftButtonPressed)
            {
                leftButtonPressedPosition = glm::vec2(event.button.x,event.button.y);
            }
            else if(bIsRightButtonPressed)
            {
                rightButtonPressedPosition = glm::vec2(event.button.x,event.button.y);
            }
            else
            {
                lastPressedButtonPosition = glm::vec2(event.button.x,event.button.y);
            }

            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:

            bIsLeftButtonReleased = event.button.button == SDL_BUTTON_LEFT;
            bIsRightButtonReleased = event.button.button == SDL_BUTTON_RIGHT;
            bIsMiddleButtonReleased = event.button.button == SDL_BUTTON_MIDDLE;
            bIsX1ButtonReleased = event.button.button == SDL_BUTTON_X1;
            bIsX2ButtonReleased = event.button.button == SDL_BUTTON_X2;

            bIsLeftButtonPressed = !bIsLeftButtonReleased;
            bIsRightButtonPressed = !bIsRightButtonReleased;
            bIsMiddleButtonPressed = !bIsMiddleButtonReleased;
            bIsX1ButtonPressed = !bIsX1ButtonReleased;
            bIsX2ButtonReleased = !bIsX2ButtonReleased;

            if(bIsLeftButtonPressed)
            {
                rightButtonReleasedPosition = glm::vec2(event.button.x,event.button.y);
            }
            else if(bIsRightButtonPressed)
            {
                leftButtonReleasedPosition = glm::vec2(event.button.x,event.button.y);
            }
            else
            {
                lastReleasedButtonPosition = glm::vec2(event.button.x,event.button.y);
            }
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

bool hexen::engine::core::input::Mouse::isRightButtonPressed() const noexcept
{
    return bIsRightButtonPressed;
}

bool hexen::engine::core::input::Mouse::isLeftButtonPressed() const noexcept
{
    return bIsLeftButtonPressed;
}

glm::vec2 hexen::engine::core::input::Mouse::getRightButtonPressedPosition() const noexcept
{
    return rightButtonPressedPosition;
}

glm::vec2 hexen::engine::core::input::Mouse::getLeftButtonPressedPosition() const noexcept
{
    return leftButtonPressedPosition;
}

glm::vec2 hexen::engine::core::input::Mouse::getLeftMouseReleasedPosition() const noexcept
{
    return leftButtonReleasedPosition;
}

glm::vec2 hexen::engine::core::input::Mouse::getRightMouseReleasedPosition() const noexcept
{
    return rightButtonReleasedPosition;
}

bool hexen::engine::core::input::Mouse::isLeftButtonReleased() const noexcept
{
    return bIsLeftButtonReleased;
}

bool hexen::engine::core::input::Mouse::isRightButtonReleased() const noexcept
{
    return bIsRightButtonReleased;
}

glm::vec2 hexen::engine::core::input::Mouse::getWheelPosition() const noexcept
{
    return wheelPosition;
}

bool hexen::engine::core::input::Mouse::isMiddleButtonPressed() const noexcept
{
    return bIsMiddleButtonPressed;
}


bool hexen::engine::core::input::Mouse::isMiddleButtonReleased() const noexcept
{
    return bIsMiddleButtonReleased;
}

bool hexen::engine::core::input::Mouse::isX1ButtonPressed() const noexcept
{
    return bIsX1ButtonPressed;
}

bool hexen::engine::core::input::Mouse::isX2ButtonPressed() const noexcept
{
    return bIsX2ButtonPressed;
}

bool hexen::engine::core::input::Mouse::isX1ButtonReleased() const noexcept
{
    return bIsX1ButtonReleased;
}

bool hexen::engine::core::input::Mouse::isX2ButtonReleased() const noexcept
{
    return bIsX2ButtonReleased;
}

glm::vec2 hexen::engine::core::input::Mouse::getLastPressedButtonPosition() const noexcept
{
    return lastPressedButtonPosition;
}

glm::vec2 hexen::engine::core::input::Mouse::getLastReleasedButtonPosition() const noexcept
{
    return lastReleasedButtonPosition;
}


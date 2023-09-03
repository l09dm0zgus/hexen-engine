//
// Created by cx9ps3 on 03.09.2023.
//

#include "Mouse.h"

void core::input::Mouse::proccessInput(const SDL_Event &event)
{
    switch (event.type)
    {
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            bIsLeftButtonPressed = event.button.button == SDL_BUTTON_LEFT;
            bIsRightButtonPressed = event.button.button == SDL_BUTTON_RIGHT;
            bIsMiddleButtonPressed = event.button.button == SDL_BUTTON_MIDDLE;
            bIsX1ButtonPressed = event.button.button == SDL_BUTTON_X1;
            bIsX2ButtonPressed = event.button.button == SDL_BUTTON_X2;


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
            bIsLeftMouseReleased = event.button.button == SDL_BUTTON_LEFT;
            bIsRightMouseReleased = event.button.button == SDL_BUTTON_RIGHT;
            bIsMiddleButtonReleased = event.button.button == SDL_BUTTON_MIDDLE;
            bIsX1ButtonReleased = event.button.button == SDL_BUTTON_X1;
            bIsX2ButtonReleased = event.button.button == SDL_BUTTON_X2;

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

glm::vec2 core::input::Mouse::getPosition() const noexcept
{
    return position;
}

bool core::input::Mouse::isRightButtonPressed() const noexcept
{
    return bIsRightButtonPressed;
}

bool core::input::Mouse::isLeftButtonPressed() const noexcept
{
    return bIsLeftButtonPressed;
}

glm::vec2 core::input::Mouse::getRightButtonPressedPosition() const noexcept
{
    return rightButtonPressedPosition;
}

glm::vec2 core::input::Mouse::getLeftButtonPressedPosition() const noexcept
{
    return leftButtonPressedPosition;
}

glm::vec2 core::input::Mouse::getLeftMouseReleasedPosition() const noexcept
{
    return leftButtonReleasedPosition;
}

glm::vec2 core::input::Mouse::getRightMouseReleasedPosition() const noexcept
{
    return rightButtonReleasedPosition;
}

bool core::input::Mouse::isLeftMouseReleased() const noexcept
{
    return bIsLeftMouseReleased;
}

bool core::input::Mouse::isRightMouseReleased() const noexcept
{
    return bIsRightMouseReleased;
}

glm::vec2 core::input::Mouse::getWheelPosition() const noexcept
{
    return wheelPosition;
}

bool core::input::Mouse::isMiddleButtonPressed() const noexcept
{
    return bIsMiddleButtonPressed;
}


bool core::input::Mouse::isMiddleMouseReleased() const noexcept
{
    return bIsMiddleButtonReleased;
}

bool core::input::Mouse::isX1ButtonPressed() const noexcept
{
    return bIsX1ButtonPressed;
}

bool core::input::Mouse::isX2ButtonPressed() const noexcept
{
    return bIsX2ButtonPressed;
}

bool core::input::Mouse::isX1ButtonReleased() const noexcept
{
    return bIsX1ButtonReleased;
}

bool core::input::Mouse::isX2ButtonReleased() const noexcept
{
    return bIsX2ButtonReleased;
}

glm::vec2 core::input::Mouse::getLastPressedButtonPosition() const noexcept
{
    return lastPressedButtonPosition;
}

glm::vec2 core::input::Mouse::getLastReleasedButtonPosition() const noexcept
{
    return lastReleasedButtonPosition;
}


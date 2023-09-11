//
// Created by cx9ps3 on 11.09.2023.
//

#include "Gamepad.hpp"
#include <algorithm>

std::vector<std::shared_ptr<hexen::engine::core::input::Gamepad>> hexen::engine::core::input::Gamepad::gamepads;

hexen::engine::core::input::Gamepad::Gamepad(hexen::engine::core::i32 index)
{
    controller = SDL_OpenGamepad(index);
    if (controller == nullptr)
    {
        SDL_Log("Failed to open device controller : %s",SDL_GetError());
    }
    gamepadID = SDL_GetGamepadInstanceID(controller);
    name = SDL_GetGamepadName(controller);
    std::cout << "Added gamepad : " << name << std::endl;
}

void hexen::engine::core::input::Gamepad::processInput(const SDL_Event &event)
{
    switch (event.type)
    {
        case SDL_EVENT_GAMEPAD_AXIS_MOTION:
            switch (event.gaxis.axis)
            {
                case SDL_GAMEPAD_AXIS_LEFTX:
                    leftAxisX = event.gaxis.value;
                    break;
                case SDL_GAMEPAD_AXIS_LEFTY:
                    leftAxisY = event.gaxis.value;
                    break;
                case SDL_GAMEPAD_AXIS_RIGHTX:
                    rightAxisX = event.gaxis.value;
                    break;
                case SDL_GAMEPAD_AXIS_RIGHTY:
                    rightAxisY = event.gaxis.value;
                    break;
            }
            break;
        case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
            buttonEvent = event.gbutton;
            break;
        case SDL_EVENT_GAMEPAD_BUTTON_UP:
            buttonEvent = event.gbutton;
            break;
    }
}


bool hexen::engine::core::input::Gamepad::isButtonPressed(hexen::engine::core::input::Gamepad::Button button) const
{
    return static_cast<u32>(button) == buttonEvent.type;
}


bool hexen::engine::core::input::Gamepad::isButtonReleased(hexen::engine::core::input::Gamepad::Button button) const
{
    return static_cast<u32>(button) == buttonEvent.type;
}

std::string hexen::engine::core::input::Gamepad::getName() const noexcept
{
    return name;
}

float hexen::engine::core::input::Gamepad::getLeftThumbstickX() const noexcept
{
    return leftAxisX;
}

float hexen::engine::core::input::Gamepad::getRightThumbstickX() const noexcept
{
    return rightAxisX;
}

float hexen::engine::core::input::Gamepad::getLeftThumbstickY() const noexcept
{
    return leftAxisY;
}

float hexen::engine::core::input::Gamepad::getRightThumbstickY() const noexcept
{
    return rightAxisY;
}

std::vector<std::shared_ptr<hexen::engine::core::input::Gamepad>> hexen::engine::core::input::Gamepad::getAllAvailableGamepads()
{
    i32  numbersOfGamepads;
    auto joysticksIDs = SDL_GetGamepads(&numbersOfGamepads);

    gamepads.reserve(numbersOfGamepads);

    for(i32 i = 0; i < numbersOfGamepads; i++)
    {
        gamepads.emplace_back(std::make_unique<Gamepad>(i));
    }

    return gamepads;
}

hexen::engine::core::input::Gamepad::~Gamepad()
{
    SDL_CloseGamepad(controller);
}

SDL_JoystickID hexen::engine::core::input::Gamepad::getID() const noexcept
{
    return gamepadID;
}

void hexen::engine::core::input::Gamepad::addNewGamepad(SDL_JoystickID gamepadID)
{
    gamepads.emplace_back(std::make_unique<Gamepad>(gamepadID));
}

void hexen::engine::core::input::Gamepad::removeNewGamepad(SDL_JoystickID gamepadID)
{
    auto it = std::find_if(gamepads.begin(), gamepads.end(),[gamepadID = gamepadID](const std::shared_ptr<Gamepad> &gamepad){
        return gamepadID == gamepad->getID();
    });

    if(it != gamepads.end())
    {
        gamepads.erase(it);
    }
}


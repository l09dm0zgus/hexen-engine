//
// Created by cx9ps3 on 02.09.2023.
//

#include "InputSystem.hpp"
#include <fstream>
#include <filesystem>
#include "../core/window/Window.hpp"
#include "../core/input_devices/Gamepad.hpp"

void hexen::engine::systems::InputSystem::processInput(const std::shared_ptr<core::Window> &window)
{
    SDL_Event event;
    while (window->pollEvents(&event))
    {
        for(auto& gui : guis)
        {
            gui->processEvent(event);
        }

        mouse->processInput(event);
        keyboard->processInput(event);

        for(auto& gamepad : gamepads)
        {
            gamepad->processInput(event);
        }

        if (event.type == SDL_EVENT_QUIT || event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED || keyboard->isKeyPressed(core::input::Keyboard::Key::ESCAPE))
        {
            window->close();
        }
        else if (event.type == SDL_EVENT_WINDOW_RESIZED)
        {
            window->resize();
        }
        else if (event.type == SDL_EVENT_GAMEPAD_ADDED)
        {
            core::input::Gamepad::addNewGamepad(event.gdevice.which);
        }
        else if (event.type == SDL_EVENT_GAMEPAD_REMOVED)
        {
            core::input::Gamepad::removeNewGamepad(event.gdevice.which);
        }
    }

    window->pollEvents(&event);
}

hexen::engine::systems::InputSystem::InputSystem(const std::string &pathToFile)
{
    path = pathToFile;
    if(std::filesystem::exists(pathToFile))
    {
        loadMappingsFile();
    }
    else
    {
        createMappingsFile();
    }

    keyboard = core::memory::make_unique<core::input::Keyboard>();
    mouse = core::memory::make_unique<core::input::Mouse>();
    gamepads =  core::input::Gamepad::getAllAvailableGamepads();

}

void hexen::engine::systems::InputSystem::createMappingsFile()
{
    keyMappingsFile["mappings"]["number_of_actions"] = 0;
    keyMappingsFile["mappings"]["number_of_axis"] = 0;
    std::ofstream file(path);
    file << keyMappingsFile.dump(2);

}

void hexen::engine::systems::InputSystem::loadMappingsFile()
{
    std::ifstream file(path);
    keyMappingsFile = nlohmann::json::parse(file);

    auto numberOfAxisMappings = keyMappingsFile["mappings"]["number_of_axis"];
    auto numberOfActionMappings = keyMappingsFile["mappings"]["number_of_actions"];

    for(core::i32 i = 0; i < numberOfAxisMappings; i++)
    {
        axisMappings.emplace_back(keyMappingsFile["mappings"]["axis_mappings"][i]["axis_name"],keyMappingsFile["mappings"]["axis_mappings"][i]["value"],keyMappingsFile["mappings"]["axis_mappings"][i]["axis_key"]);
    }

    for(core::i32 i = 0; i < numberOfActionMappings; i++)
    {
        actionMappings.emplace_back(keyMappingsFile["mapping"]["action_mappings"][i]["action_name"],keyMappingsFile["mapping"]["action_mappings"][i]["action_key"]);
    }
}

void  hexen::engine::systems::InputSystem::addGUI(const std::shared_ptr<gui::IGUI> &gui)
{
    guis.push_back(gui);
}

void  hexen::engine::systems::InputSystem::addNewAxisMapping(const std::string &name, float value, core::u32 sdlKey)
{

}

void hexen::engine::systems::InputSystem::addNewAxisMapping(const hexen::engine::systems::InputSystem::AxisMapping &axisMapping)
{

}

void hexen::engine::systems::InputSystem::addNewActionMapping(const std::string &name, core::u32 sdlKey)
{

}

void hexen::engine::systems::InputSystem::addNewActionMapping(const hexen::engine::systems::InputSystem::ActionMapping &actionMapping)
{

}

void hexen::engine::systems::InputSystem::bindAction(const std::string &name, const std::function<void()> &actionCallback)
{

}

void hexen::engine::systems::InputSystem::bindAxis(const std::string &name, const std::function<void(float)> &axisCallback)
{

}

void hexen::engine::systems::InputSystem::changeMapping(const std::string &name, core::u32, core::u32 newKey)
{

}

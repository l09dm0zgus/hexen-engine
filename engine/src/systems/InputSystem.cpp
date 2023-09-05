//
// Created by cx9ps3 on 02.09.2023.
//

#include "InputSystem.h"
#include <fstream>
#include <filesystem>
#include "../core/window/Window.h"

void sys::input::InputSystem::processInput(const std::shared_ptr<core::Window> &window)
{
    SDL_Event event;
    while (window->pollEvents(&event))
    {
        for(auto& gui : guis)
        {
            gui->processEvent(event);
        }
        mouse->processInput(event);

        std::cout << "Pressed Left button: " <<std::boolalpha << mouse->isLeftButtonPressed() << " pressed Right button: " << std::boolalpha << mouse->isRightButtonPressed() << " pressed middle button: " << std::boolalpha << mouse->isMiddleButtonPressed() << " is x1 button pressed : " << std::boolalpha << mouse->isX1ButtonPressed() << " is x2 button pressed : " << std::boolalpha << mouse->isX2ButtonPressed() << "\n";
        std::cout << "Released Left button: " << std::boolalpha << mouse->isLeftButtonReleased() << " released  right button: " << std::boolalpha << mouse->isRightButtonReleased() << " released middle button: " << std::boolalpha << mouse->isMiddleButtonReleased() << " is released x1 button : " << std::boolalpha << mouse->isX1ButtonReleased() << " is x2 button released button: " << std::boolalpha << mouse->isX2ButtonReleased() << "\n";

        if (event.type == SDL_EVENT_QUIT || event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
        {
            window->close();
        }
        else if (event.type == SDL_EVENT_WINDOW_RESIZED)
        {
            window->resize();
        }
    }

    window->pollEvents(&event);
}

sys::input::InputSystem::InputSystem(const std::string &pathToFile)
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

    mouse = core::mem::make_unique<core::input::Mouse>();
}

void sys::input::InputSystem::createMappingsFile()
{
    keyMappingsFile["mappings"]["number_of_actions"] = 0;
    keyMappingsFile["mappings"]["number_of_axis"] = 0;
    std::ofstream file(path);
    file << keyMappingsFile.dump(2);

}

void sys::input::InputSystem::loadMappingsFile()
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

void sys::input::InputSystem::addGUI(const std::shared_ptr<gui::IGUI> &gui)
{
    guis.push_back(gui);
}

void sys::input::InputSystem::addNewAxisMapping(const std::string &name, float value, core::u32 sdlKey)
{

}

void sys::input::InputSystem::addNewAxisMapping(const sys::input::InputSystem::AxisMapping &axisMapping)
{

}

void sys::input::InputSystem::addNewActionMapping(const std::string &name, core::u32 sdlKey)
{

}

void sys::input::InputSystem::addNewActionMapping(const sys::input::InputSystem::ActionMapping &actionMapping)
{

}

void sys::input::InputSystem::bindAction(const std::string &name, const std::function<void()> &actionCallback)
{

}

void sys::input::InputSystem::bindAxis(const std::string &name, const std::function<void(float)> &axisCallback)
{

}

void sys::input::InputSystem::changeMapping(const std::string &name, core::u32, core::u32 newKey)
{

}

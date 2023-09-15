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

        processKeyboardInput(event);
        processGamepadsInput(event);

        mouse->processInput(event);

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
        axisMappings.emplace_back(keyMappingsFile["mappings"]["axis_mappings"][i]["axis_name"], keyMappingsFile["mappings"]["axis_mappings"][i]["value"], keyMappingsFile["mappings"]["axis_mappings"][i]["axis_key"],keyMappingsFile["mappings"]["axis_mappings"][i]["player_id"]);
    }

    for(core::i32 i = 0; i < numberOfActionMappings; i++)
    {
        actionMappings.emplace_back(keyMappingsFile["mapping"]["action_mappings"][i]["action_name"], keyMappingsFile["mapping"]["action_mappings"][i]["action_key"], keyMappingsFile["mapping"]["action_mappings"][i]["player_id"]);
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

void hexen::engine::systems::InputSystem::processKeyboardInput(const SDL_Event &event)
{
    if(keyboard->processInput(event))
    {
        ActionMapping actionMapping;
        AxisMapping axisMapping;
        if(findActionMappingById(keyboard->currentKeyScancode,actionMapping))
        {
            auto callback  = findActionMappingCallback(actionMapping.playerId,actionMapping.name);
            callback();
            return;
        }
        else if(findAxisMappingById(keyboard->currentKeyScancode,axisMapping))
        {
            auto callback = findAxisMappingCallback(axisMapping.playerId,axisMapping.name);
            callback(axisMapping.value);
            return;
        }
    }
}

bool hexen::engine::systems::InputSystem::findActionMappingById(hexen::engine::core::u32 id,hexen::engine::systems::InputSystem::ActionMapping &actionMapping)
{
    auto actionMappingsIterator = std::find_if(actionMappings.cbegin(),actionMappings.cend(),[id = id](const ActionMapping& actionMapping){
        return actionMapping.sdlKey == id;
    });

    if(actionMappingsIterator != actionMappings.cend())
    {
        actionMapping = *actionMappingsIterator;
        return true;
    }
    return false;

}

bool hexen::engine::systems::InputSystem::findAxisMappingById(hexen::engine::core::u32 id,hexen::engine::systems::InputSystem::AxisMapping &axisMapping)
{
    auto axisMappingsIterator = std::find_if(axisMappings.cbegin(),axisMappings.cend(),[id = id](const AxisMapping& axisMapping){
        return axisMapping.sdlKey == id;
    });

    if(axisMappingsIterator != axisMappings.cend())
    {
        axisMapping = *axisMappingsIterator;
        return true;
    }

    return false;
}

void hexen::engine::systems::InputSystem::processGamepadsInput(const SDL_Event &event)
{
    auto players = 0;
    for(auto& gamepad : gamepads)
    {
        if(gamepad->processInput(event))
        {
            ActionMapping actionMapping;
            AxisMapping axisMapping;
            auto currentEventId = gamepad->currentEventId;

            if(findActionMappingById(currentEventId,actionMapping))
            {
                auto callback  = findActionMappingCallback(players,actionMapping.name);
                callback();
                return;
            }
            else if(findAxisMappingById(currentEventId,axisMapping))
            {
                auto axis = static_cast<core::input::Gamepad::Axis>(currentEventId);
                auto axisValue = 0.0f;

                switch(axis)
                {
                    case core::input::Gamepad::Axis::LEFT_X:
                        axisValue = gamepad->getLeftThumbstickX();
                        break;
                    case core::input::Gamepad::Axis::LEFT_Y:
                        axisValue = gamepad->getLeftThumbstickY();
                        break;
                    case core::input::Gamepad::Axis::RIGHT_X:
                        axisValue = gamepad->getRightThumbstickX();
                        break;
                    case core::input::Gamepad::Axis::RIGHT_Y:
                        axisValue = gamepad->getRightThumbstickY();
                        break;
                }

                auto callback = findAxisMappingCallback(players,axisMapping.name);
                callback((axisValue / MAX_GAMEPAD_AXIS_VALUE) * axisMapping.value);

                return;
            }
        }

        players++;
    }
}

hexen::engine::systems::InputSystem::ActionMappingCallback hexen::engine::systems::InputSystem::findActionMappingCallback(hexen::engine::core::u32 playerId ,const std::string &name)
{
    auto it = std::find_if(actionMappingCallbacks.cbegin(), actionMappingCallbacks.cend(),[&name,playerId = playerId](const ActionMappingCallback &callback){
        return callback.playerId == playerId && callback.name == name;
    });

    HEXEN_ASSERT(it != actionMappingCallbacks.cend() ,"Not founded callback to this player\n");

    return *it;
}

hexen::engine::systems::InputSystem::AxisMappingCallback hexen::engine::systems::InputSystem::findAxisMappingCallback(hexen::engine::core::u32 playerId, const std::string &name)
{
    auto it = std::find_if(axisMappingCallbacks.cbegin(), axisMappingCallbacks.cend(),[&name,playerId = playerId](const AxisMappingCallback &callback){
        return callback.playerId == playerId && callback.name == name;
    });

    HEXEN_ASSERT(it != axisMappingCallbacks.cend() ,"Not founded callback to this player \n");

    return *it;
}


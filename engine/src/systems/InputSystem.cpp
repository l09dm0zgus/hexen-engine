//
// Created by cx9ps3 on 02.09.2023.
//

#include "InputSystem.hpp"
#include "../core/exceptions/MappingNotFound.hpp"
#include "../core/input_devices/Gamepad.hpp"
#include "../core/window/Window.hpp"
#include <filesystem>
#include <fstream>
#include <execution>

void hexen::engine::systems::InputSystem::processInput(const std::shared_ptr<core::Window> &window)
{
	HEXEN_ADD_TO_PROFILE();
	SDL_Event event;

	while (window->pollEvents(&event))
	{
		windowSize = window->getSize();

		processKeyboardInput(event);
		processGamepadsInput(event);
		processMouseInput(event);

		for (auto &gui : guis)
		{
			gui->processEvent(event);
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
	HEXEN_ADD_TO_PROFILE();

	path = pathToFile;
	if (std::filesystem::exists(pathToFile))
	{
		loadMappingsFile();
	}
	else
	{
		createMappingsFile();
	}

	keyboard = core::memory::make_unique<core::input::Keyboard>();
	mouse = core::memory::make_unique<core::input::Mouse>();
	gamepads = core::input::Gamepad::getAllAvailableGamepads();
}


void hexen::engine::systems::InputSystem::createMappingsFile()
{
	HEXEN_ADD_TO_PROFILE();
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

	for (core::i32 i = 0; i < numberOfAxisMappings; i++)
	{
		axisMappings.emplace_back(keyMappingsFile["mappings"]["axis_mappings"][i]["axis_name"], keyMappingsFile["mappings"]["axis_mappings"][i]["value"], keyMappingsFile["mappings"]["axis_mappings"][i]["axis_key"], keyMappingsFile["mappings"]["axis_mappings"][i]["player_id"]);
	}

	for (core::i32 i = 0; i < numberOfActionMappings; i++)
	{
		actionMappings.emplace_back(keyMappingsFile["mapping"]["action_mappings"][i]["action_name"], keyMappingsFile["mapping"]["action_mappings"][i]["action_key"], keyMappingsFile["mapping"]["action_mappings"][i]["player_id"]);
	}
}

void hexen::engine::systems::InputSystem::addGUI(const std::shared_ptr<gui::IGUI> &gui)
{
	HEXEN_ADD_TO_PROFILE();
	guis.push_back(gui);
}


void hexen::engine::systems::InputSystem::addNewAxisMapping(const std::string &name, float value, core::u32 sdlKey, core::u8 playerId)
{
	HEXEN_ADD_TO_PROFILE();
	axisMappings.emplace_back(name, value, sdlKey, playerId);
}


void hexen::engine::systems::InputSystem::addNewAxisMapping(const hexen::engine::systems::InputSystem::AxisMapping &axisMapping)
{
	HEXEN_ADD_TO_PROFILE();
	axisMappings.push_back(axisMapping);
}

void hexen::engine::systems::InputSystem::addNewActionMapping(const std::string &name, core::u32 sdlKey, core::u8 playerId)
{
	HEXEN_ADD_TO_PROFILE();
	actionMappings.emplace_back(name, sdlKey, playerId);
}

void hexen::engine::systems::InputSystem::addNewActionMapping(const hexen::engine::systems::InputSystem::ActionMapping &actionMapping)
{
	HEXEN_ADD_TO_PROFILE();
	actionMappings.push_back(actionMapping);
}


void hexen::engine::systems::InputSystem::bindAction(const std::string &name, const std::function<void()> &actionCallback, bool enableForMultiplePLayers, core::u32 playerId)
{
	HEXEN_ADD_TO_PROFILE();
	ActionMappingCallback callback(actionCallback, name);

	if (enableForMultiplePLayers)
	{
		callback.playerId = playerId;
	}
	else
	{
		callback.playerId = 0;
	}

	actionMappingCallbacks.push_back(callback);
}

void hexen::engine::systems::InputSystem::bindAxis(const std::string &name, const std::function<void(float)> &axisCallback, bool enableForMultiplePLayers, core::u32 playerId)
{
	HEXEN_ADD_TO_PROFILE();
	AxisMappingCallback callback(axisCallback, name);

	if (enableForMultiplePLayers)
	{
		callback.playerId = playerId;
	}
	else
	{
		callback.playerId = 0;
	}

	axisMappingCallbacks.push_back(callback);
}

void hexen::engine::systems::InputSystem::changeMapping(const std::string &name, core::u32 newKey)
{
	HEXEN_ADD_TO_PROFILE();
	auto actionMappingsIterator = std::find_if(actionMappings.begin(), actionMappings.end(), [&name](const ActionMapping &mapping)
			{ return mapping.name == name; });

	auto axisMappingsIterator = std::find_if(axisMappings.begin(), axisMappings.end(), [&name](const AxisMapping &mapping)
			{ return mapping.name == name; });

	if (actionMappingsIterator != actionMappings.end())
	{
		actionMappingsIterator->sdlKey = newKey;
	}
	else if (axisMappingsIterator != axisMappings.end())
	{
		axisMappingsIterator->sdlKey = newKey;
	}
	else
	{
		throw hexen::engine::exceptions::MappingNotFound(name);
	}
}

void hexen::engine::systems::InputSystem::processKeyboardInput(const SDL_Event &event)
{
	HEXEN_ADD_TO_PROFILE();
	if (keyboard->processInput(event))
	{
		std::vector<ActionMapping> foundActionMapping;
		std::vector<AxisMapping> foundAxisMapping;
		if (findActionMappingsById(keyboard->currentKeyScancode, foundActionMapping))
		{
			for(const auto &actionMapping : foundActionMapping)
			{
				if(actionMapping.isEnableInput)
				{
					auto callback = findActionMappingCallback(actionMapping.playerId, actionMapping.name);
					callback();
				}
			}
		}
		else if (findAxisMappingsById(keyboard->currentKeyScancode, foundAxisMapping))
		{
			for(const auto &axisMapping : foundAxisMapping)
			{
				if(axisMapping.isEnableInput)
				{
					auto callback = findAxisMappingCallback(axisMapping.playerId, axisMapping.name);
					callback(axisMapping.value);
				}
			}
		}
	}
}

bool hexen::engine::systems::InputSystem::findActionMappingsById(core::u32 id, std::vector<ActionMapping> &foundMappings)
{
	HEXEN_ADD_TO_PROFILE();
	std::for_each(actionMappings.cbegin(), actionMappings.cend(), [&foundMappings, id = id](const ActionMapping &actionMapping){
				if(actionMapping.sdlKey == id)
				{
					foundMappings.push_back(actionMapping);
				}
	});
	return !foundMappings.empty();
}

bool hexen::engine::systems::InputSystem::findAxisMappingsById(core::u32 id, std::vector<AxisMapping> &foundMappings)
{
	HEXEN_ADD_TO_PROFILE();
	std::for_each(axisMappings.cbegin(), axisMappings.cend(), [&foundMappings, id = id](const AxisMapping &actionMapping){
				if(actionMapping.sdlKey == id)
				{
					foundMappings.push_back(actionMapping);
				}
			});
	return !foundMappings.empty();
}

void hexen::engine::systems::InputSystem::processGamepadsInput(const SDL_Event &event)
{
	HEXEN_ADD_TO_PROFILE();
	auto players = 0;
	for (auto &gamepad : gamepads)
	{
		if (gamepad->processInput(event))
		{
			std::vector<ActionMapping> foundActionMapping;
			std::vector<AxisMapping> foundAxisMapping;

			auto currentEventId = gamepad->currentEventId;
			if (findActionMappingsById(currentEventId, foundActionMapping))
			{
				for(const auto &actionMapping : foundActionMapping)
				{
					if(actionMapping.isEnableInput)
					{
						auto callback = findActionMappingCallback(players, actionMapping.name);
						callback();
					}
				}

			}
			else if (findAxisMappingsById(currentEventId, foundAxisMapping))
			{
				for(const auto &axisMapping : foundAxisMapping)
				{
					auto axis = static_cast<core::input::Gamepad::Axis>(currentEventId);
					auto axisValue = 0.0f;

					switch (axis)
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

					if(axisMapping.isEnableInput)
					{
						auto callback = findAxisMappingCallback(players, axisMapping.name);
						callback((axisValue / MAX_GAMEPAD_AXIS_VALUE) * axisMapping.value);
					}
				}
			}
		}
		players++;
	}
}


hexen::engine::systems::InputSystem::ActionMappingCallback hexen::engine::systems::InputSystem::findActionMappingCallback(hexen::engine::core::u32 playerId, const std::string &name)
{
	HEXEN_ADD_TO_PROFILE();
	auto it = std::find_if(actionMappingCallbacks.cbegin(), actionMappingCallbacks.cend(), [&name, playerId = playerId](const ActionMappingCallback &callback)
			{ return callback.playerId == playerId && callback.name == name; });

	HEXEN_ASSERT(it != actionMappingCallbacks.cend(), "Not founded callback to this player\n");

	return *it;
}

hexen::engine::systems::InputSystem::AxisMappingCallback hexen::engine::systems::InputSystem::findAxisMappingCallback(hexen::engine::core::u32 playerId, const std::string &name)
{
	HEXEN_ADD_TO_PROFILE();
	auto it = std::find_if(axisMappingCallbacks.cbegin(), axisMappingCallbacks.cend(), [&name, playerId = playerId](const AxisMappingCallback &callback)
			{ return callback.playerId == playerId && callback.name == name; });

	HEXEN_ASSERT(it != axisMappingCallbacks.cend(), "Not founded callback to this player \n");

	return *it;
}

void hexen::engine::systems::InputSystem::processMouseInput(const SDL_Event &event)
{
	HEXEN_ADD_TO_PROFILE();
	if (mouse->processInput(event))
	{
		std::vector<ActionMapping> foundActionMapping;
		std::vector<AxisMapping> foundAxisMapping;

		if (findActionMappingsById(mouse->currentButton, foundActionMapping))
		{
			for(const auto &actionMapping : foundActionMapping)
			{
				if(actionMapping.isEnableInput)
				{
					auto callback = findActionMappingCallback(0, actionMapping.name);
					callback();
				}
			}

		}
		else if (findAxisMappingsById(mouse->currentButton, foundAxisMapping))
		{
			for(const auto &axisMapping : foundAxisMapping)
			{
				auto axis = 0.0f;
				if (mouse->isMouseMovingOnX)
				{
					axis = mouse->getPosition().x / windowSize.x;
				}
				else if (mouse->isMouseMovingOnY)
				{
					axis = mouse->getPosition().y / windowSize.y;
				}
				else if (mouse->isMouseWheelMovingOnX)
				{
					axis = mouse->getWheelPosition().x;
				}
				else if (mouse->isMouseWheelMovingOnY)
				{
					axis = mouse->getWheelPosition().y;
				}

				if(axisMapping.isEnableInput)
				{
					auto callback = findAxisMappingCallback(0, axisMapping.name);
					callback(axis * axisMapping.value);
				}
			}
		}
	}
}

void hexen::engine::systems::InputSystem::saveMappings()
{
	HEXEN_ADD_TO_PROFILE();
	std::ofstream file(path);

	keyMappingsFile["mappings"]["number_of_axis"] = axisMappings.size();
	keyMappingsFile["mappings"]["number_of_actions"] = actionMappings.size();

	core::u32 i = 0;
	for (const auto &mapping : axisMappings)
	{
		keyMappingsFile["mappings"]["axis_mappings"][i]["axis_name"] = mapping.name;
		keyMappingsFile["mappings"]["axis_mappings"][i]["value"] = mapping.value;
		keyMappingsFile["mappings"]["axis_mappings"][i]["axis_key"] = mapping.sdlKey;
		keyMappingsFile["mappings"]["axis_mappings"][i]["player_id"] = mapping.playerId;
		i++;
	}

	i = 0;
	for (const auto &mapping : actionMappings)
	{
		keyMappingsFile["mapping"]["action_mappings"][i]["action_name"] = mapping.name;
		keyMappingsFile["mapping"]["action_mappings"][i]["action_key"] = mapping.playerId;
		keyMappingsFile["mapping"]["action_mappings"][i]["player_id"] = mapping.sdlKey;
		i++;
	}

	file << keyMappingsFile.dump(2);
}

void hexen::engine::systems::InputSystem::enableInputByPlayerID(hexen::engine::core::u32 playerID, bool isEnable)
{
	HEXEN_ADD_TO_PROFILE();
	std::for_each(std::execution::par, axisMappings.begin(), axisMappings.end(),[isEnable = isEnable, playerID = playerID](AxisMapping& axisMapping){
				if(axisMapping.playerId == playerID)
				{
					axisMapping.isEnableInput = isEnable;
				}
	});

	std::for_each(std::execution::par, actionMappings.begin(), actionMappings.end(),[isEnable = isEnable, playerID = playerID](ActionMapping& actionMapping){
				if(actionMapping.playerId == playerID)
				{
					actionMapping.isEnableInput = isEnable;
				}
			});
}

//
// Created by cx9ps3 on 13.07.2023.
//

#include "SystemsManager.hpp"
#include "../core/window/Window.hpp"
#include "input/InputHelper.hpp"
#include "input/InputSystem.hpp"
#include <TaskSystem.hpp>
#include <memory>


hexen::engine::systems::SystemsManager *hexen::engine::systems::SystemsManager::currentSystemManager {nullptr};

void hexen::engine::systems::SystemsManager::processInput(const std::shared_ptr<core::Window> &window)
{
	HEXEN_ADD_TO_PROFILE();
	inputSystem->processInput(window);
}

void hexen::engine::systems::SystemsManager::start()
{
	HEXEN_ADD_TO_PROFILE();
	for (auto &system : gameplaySystems)
	{
		threads::TaskSystem::addTask(core::threading::TaskPriority::High, system.get(), &IGamePlaySystem::start);
	}
}

void hexen::engine::systems::SystemsManager::render(float alpha)
{
	HEXEN_ADD_TO_PROFILE();
	for (auto &system : renderSystems)
	{
		threads::TaskSystem::addTask(core::threading::TaskPriority::High, system.get(), &IRenderSystem::render, alpha);
	}
}

void hexen::engine::systems::SystemsManager::update(float deltaTime)
{
	HEXEN_ADD_TO_PROFILE();
	for (auto &system : gameplaySystems)
	{
		threads::TaskSystem::addTask(core::threading::TaskPriority::High, system.get(), &IGamePlaySystem::update, deltaTime);
	}
}

hexen::engine::systems::SystemsManager::SystemsManager()
{
	HEXEN_ADD_TO_PROFILE();
	inputSystem = input::InputHelper::createInputSystem();
}
std::shared_ptr<hexen::engine::systems::InputSystem> hexen::engine::systems::SystemsManager::getInputSystem()
{
	HEXEN_ADD_TO_PROFILE();
	return inputSystem;
}

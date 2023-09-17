//
// Created by cx9ps3 on 13.07.2023.
//

#include "SystemsManager.hpp"
#include "../core/window/Window.hpp"
#include "TaskSystem.hpp"
#include "InputSystem.hpp"
#include <memory>


hexen::engine::systems::SystemsManager* hexen::engine::systems::SystemsManager::currentSystemManager{nullptr};

void hexen::engine::systems::SystemsManager::processInput(const std::shared_ptr<core::Window> &window)
{
    inputSystem->processInput(window);
}

void hexen::engine::systems::SystemsManager::start()
{
    for(auto& system : renderSystems)
    {
        TaskSystem::addTask(core::threading::TaskPriority::High,system.get(),&IRenderSystem::start);
    }

    for(auto& system : gameplaySystems)
    {
        TaskSystem::addTask(core::threading::TaskPriority::High,system.get(),&IGamePlaySystem::start);
    }

}

void hexen::engine::systems::SystemsManager::render(float alpha)
{
    for(auto& system : renderSystems)
    {
        TaskSystem::addTask(core::threading::TaskPriority::High,system.get(),&IRenderSystem::render,alpha);
    }
}

void hexen::engine::systems::SystemsManager::update(float deltaTime)
{
    for(auto& system : gameplaySystems)
    {
        TaskSystem::addTask(core::threading::TaskPriority::High,system.get(),&IGamePlaySystem::update,deltaTime);
    }
}

hexen::engine::systems::SystemsManager::SystemsManager()
{
    inputSystem = hexen::engine::core::memory::make_unique<hexen::engine::systems::InputSystem>();
}

std::shared_ptr<hexen::engine::systems::InputSystem> hexen::engine::systems::SystemsManager::getInputSystem() const noexcept
{
    return inputSystem;
}

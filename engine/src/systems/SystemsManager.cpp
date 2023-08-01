//
// Created by cx9ps3 on 13.07.2023.
//

#include "SystemsManager.h"
#include "../core/window/Window.h"
#include "TaskSystem.h"
#include <memory>


sys::SystemsManager* sys::SystemsManager::currentSystemManager{nullptr};

void sys::SystemsManager::processInput(const std::shared_ptr<core::Window> &window)
{
    //in future will be created InputSystem for handling input
    SDL_Event event;
    while (window->isOpen())
    {
        while (window->pollEvents(&event))
        {
            //editorGui.processEvent(&event);
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
}

void sys::SystemsManager::start()
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

void sys::SystemsManager::render(float alpha)
{
    for(auto& system : renderSystems)
    {
        TaskSystem::addTask(core::threading::TaskPriority::High,system.get(),&IRenderSystem::render,alpha);
    }
}

void sys::SystemsManager::update(float deltaTime)
{
    for(auto& system : gameplaySystems)
    {
        TaskSystem::addTask(core::threading::TaskPriority::High,system.get(),&IGamePlaySystem::update,deltaTime);
    }
}

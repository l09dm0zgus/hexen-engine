//
// Created by cx9ps3 on 29.07.2023.
//

#include "GameLoop.h"
#include <chrono>
#include "../window/Window.h"
#include "../../systems/TaskSystem.h"
#include "../../systems/RenderSystem.h"

void core::GameLoop::start()
{
    sys::SystemManager::addRenderSystem<sys::RenderSystem>(100);
    systemManager->start();
}

void core::GameLoop::loop(const std::shared_ptr<Window> &window)
{
    initializeClock();

    while (window->isOpen())
    {
        setFrameStart();
        setAccumulator();

        //process input
        systemManager->processInput(window);

        while (accumulator > deltaTime)
        {
            //update
            systemManager->update(deltaTime);
            accumulator -= deltaTime;
        }

        //render
        systemManager->render(getAlpha());
        sys::TaskSystem::waitForCounter();
    }
}



void core::GameLoop::initializeClock()
{
    framesStart = std::chrono::steady_clock::now();

}



void core::GameLoop::setFrameStart()
{
    auto currentTime = std::chrono::steady_clock::now();

    accumulator += (currentTime - framesStart).count();

    framesStart = currentTime;

}



void core::GameLoop::setAccumulator()
{
    if(accumulator > msPerUpdate)
    {
        accumulator = msPerUpdate;
    }
}

float core::GameLoop::getAlpha()
{
    return accumulator / deltaTime;
}

core::GameLoop::GameLoop() : mem::AllocatedObject()
{
    //initialize thread and fiber pool
    sys::TaskSystem::initialize();

    systemManager = mem::make_shared<sys::SystemManager>();

    HEXEN_ASSERT(systemManager != nullptr , "System manager is nullptr!");

    sys::SystemManager::setCurrentSystemManager(systemManager.get());
}

core::GameLoop::~GameLoop()
{
    sys::SystemManager::setCurrentSystemManager(nullptr);
}

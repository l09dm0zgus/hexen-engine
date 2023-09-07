//
// Created by cx9ps3 on 29.07.2023.
//

#include "GameLoop.hpp"
#include <chrono>
#include "../window/Window.hpp"
#include "../../systems/TaskSystem.hpp"
#include "../../systems/RenderSystem.hpp"

void hexen::engine::core::GameLoop::start()
{
    systems::SystemsManager::addRenderSystem<systems::RenderSystem>(100);
    systemManager->start();
}

void hexen::engine::core::GameLoop::loop()
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
        window->clear();
        systemManager->render(getAlpha());
        window->swapBuffers();
        //render
        systemManager->render(getAlpha());
        systems::TaskSystem::waitForCounter();
    }
}



void hexen::engine::core::GameLoop::initializeClock()
{
    framesStart = std::chrono::steady_clock::now();

}



void hexen::engine::core::GameLoop::setFrameStart()
{
    auto currentTime = std::chrono::steady_clock::now();

    accumulator += (currentTime - framesStart).count();

    framesStart = currentTime;

}



void hexen::engine::core::GameLoop::setAccumulator()
{
    if(accumulator > msPerUpdate)
    {
        accumulator = msPerUpdate;
    }
}

double hexen::engine::core::GameLoop::getAlpha()
{
    return accumulator / deltaTime;
}

hexen::engine::core::GameLoop::GameLoop(const std::shared_ptr<Window> &newWindow)
{
    //initialize thread and fiber pool
    systems::TaskSystem::initialize();

    systemManager = memory::make_shared<systems::SystemsManager>();

    HEXEN_ASSERT(systemManager != nullptr , "System manager is nullptr!");

    systems::SystemsManager::setCurrentSystemManager(systemManager.get());
    window = newWindow;
}

hexen::engine::core::GameLoop::~GameLoop()
{
    systems::SystemsManager::setCurrentSystemManager(nullptr);
}

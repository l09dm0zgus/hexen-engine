//
// Created by cx9ps3 on 29.07.2023.
//

#include "GameLoop.h"
#include <chrono>
#include "../window/Window.h"

void core::GameLoop::start()
{

}

void core::GameLoop::loop(const std::shared_ptr<Window> &window)
{
    initializeClock();
    while (window->isOpen())
    {
        setFrameStart();
        //process input

        setAccumulator();

        while (accumulator > deltaTime)
        {
            //update
            accumulator -= deltaTime;
        }

        //render



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

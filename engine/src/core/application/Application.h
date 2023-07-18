//
// Created by cx9ps3 on 30.12.22.
//
#pragma once

#include "../window/Window.h"
namespace core
{
    class Application
    {
    public:
        Application();
        ~Application() = default;
        Application(const Application &application) = delete;
        Application(Application &&application) =delete;

        Application& operator=(const Application &application) = delete;
        Application& operator=(Application &&application) = delete;

        void run();
    private:
        std::unique_ptr<Window> window;
        Settings settings;

    };

}

//
// Created by cx9ps3 on 25.05.2023.
//

#pragma once

#include <core/window/Window.h>

namespace edit
{
    class Application
    {
    public:
        Application();
        void run();
    private:
        std::unique_ptr<core::Window> window;
        core::Settings settings;
    };

}



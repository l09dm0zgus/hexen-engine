//
// Created by cx9ps3 on 25.05.2023.
//

#pragma once
#include <core/window/Window.h>
#include "EditorGameLoop.h"

namespace edit
{
    class Application
    {
    public:
        Application();
        void run();
    private:
        std::shared_ptr<core::Window> window;
        std::unique_ptr<EditorGameLoop> mainGameLoop;
        core::Settings settings;
    };

}



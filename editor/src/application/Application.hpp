//
// Created by cx9ps3 on 25.05.2023.
//

#pragma once
#include "core/window/Window.hpp"
#include "EditorGameLoop.hpp"

namespace hexen::editor
{
    class Application
    {
    public:
        Application();
        void run();
    private:
        std::shared_ptr< hexen::engine::core::Window> window;
        std::unique_ptr<EditorGameLoop> mainGameLoop;
        hexen::engine::core::Settings settings;
    };

}



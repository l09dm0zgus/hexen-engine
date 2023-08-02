//
// Created by cx9ps3 on 25.05.2023.
//

#include "Application.h"


edit::Application::Application()
{
    window = core::mem::make_shared<core::Window>(settings);
    mainGameLoop = core::mem::make_unique<EditorGameLoop>(window);
}

void edit::Application::run()
{
    mainGameLoop->start();
    mainGameLoop->loop();
}

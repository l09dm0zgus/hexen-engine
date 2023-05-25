//
// Created by cx9ps3 on 25.05.2023.
//

#include "Application.h"

edit::Application::Application()
{
    window = core::mem::make_unique<core::Window>("HexenEditor");
}

void edit::Application::run()
{
    while (window->isOpen())
    {
        window->pollEvents();

        window->clear();
        window->swapBuffers();
    }
}

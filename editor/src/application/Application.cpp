//
// Created by cx9ps3 on 25.05.2023.
//

#include "Application.h"
#include "../gui/EditorGUI.h"

edit::Application::Application()
{
    window = core::mem::make_unique<core::Window>("HexenEditor");
}

void edit::Application::run()
{
    SDL_Event event;
    gui::EditorGUI editorGui(window->getSDLWindow(),window->getGLContext());

    while (window->isOpen())
    {
        while(window->pollEvents(&event))
        {
            editorGui.processEvent(&event);
            if(event.type == SDL_EVENT_QUIT || event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
            {
                window->close();
            }
            else if(event.type == SDL_EVENT_WINDOW_RESIZED)
            {
                core::i32 width;
                core::i32 height;
                SDL_GetWindowSize(window->getSDLWindow(),&width,&height);
                glViewport(0,0,width,height);
            }
        }
        window->pollEvents(&event);
        window->clear();
        editorGui.begin();
        editorGui.draw();
        editorGui.end();
        window->swapBuffers();
    }
}

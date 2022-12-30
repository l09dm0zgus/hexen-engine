//
// Created by cx9ps3 on 30.12.22.
//

#include "Application.h"

void Application::run()
{
    bool isRun = true;
    SDL_Log("Main thread started.\n");
    double dt = 1 / 60.0;
    int currentTime = SDL_GetTicks();

    while (isRun)
    {
        double newTime = SDL_GetTicks();
        double frameTime = newTime - currentTime;
        currentTime = newTime;

        while(SDL_PollEvent(&sdlEvent) != 0)
        {
            // Esc button is pressed
            if(sdlEvent.type == SDL_QUIT)
            {
                isRun = false;
            }
        }

        while ( frameTime > 0.0 )
        {
            float deltaTime = SDL_min( frameTime, dt );
            //update
            frameTime -= deltaTime;
        }
        window->clear();
        //render
        window->swapBuffers();
    }
}

Application::~Application()
{
    delete window;
    window = nullptr;
}

Application::Application()
{
    window = new Window("Battleblaze");
    SDL_Log("Main window created.\n");
}

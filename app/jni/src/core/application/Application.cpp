//
// Created by cx9ps3 on 30.12.22.
//

#include "Application.h"
#include "../graphics/Graphics.h"

void Application::run()
{
    bool isRun = true;
    SDL_Log("Main thread started.\n");
    double dt = 1 / 60.0;
    int currentTime = SDL_GetTicks();
    Sprite rectangle("shaders/SpriteVertexShader.glsl", "shaders/SpriteFragmentShader.glsl");
    rectangle.addTexture("images/test.jpg");
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
        rectangle.render();
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

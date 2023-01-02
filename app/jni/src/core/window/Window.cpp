//
// Created by cx9ps3 on 28.12.22.
//

#include "Window.h"
#include <GLES3/gl31.h>

Window::Window(const std::string &title)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        SDL_Log( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }
    else
    {
        if( SDL_GetCurrentDisplayMode( 0, &displayMode ) == 0 )
        {
            width = displayMode.w;
            height = displayMode.h;
        }

        //Create window
        window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,SDL_WINDOW_FULLSCREEN_DESKTOP);
        if(window == nullptr )
        {
            SDL_Log( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            glContext = SDL_GL_CreateContext(window);
            if( glContext == nullptr )
            {
                SDL_Log( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
            }
        }
    }

}

void Window::close()
{
    SDL_DestroyWindow(window);
    window = nullptr;
//Quit SDL subsystems
    SDL_Quit();
}

void Window::swapBuffers()
{
    SDL_GL_SwapWindow(window);
}

void Window::clear()
{
    // Set background color as cornflower blue
    glClearColor(0.39f, 0.58f, 0.93f, 1.f);
    // Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Window::~Window()
{
 SDL_Log("Main Window has been destroyed.\n");
 close();
}

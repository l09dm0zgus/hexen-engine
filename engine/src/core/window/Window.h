//
// Created by cx9ps3 on 28.12.22.
//

#ifndef BATTLEBLAZE_WINDOW_H
#define BATTLEBLAZE_WINDOW_H

#include <SDL3/SDL.h>
#include <string>
#include "../memory_pool/AllocatedObject.h"
namespace core
{
    class Window : public mem::AllocatedObject
    {
    public:
        explicit Window(std::string title);
        explicit Window(std::string title,i32 width,i32 height);
        ~Window() override;
        void swapBuffers();
        void close();
        void clear();
        bool isOpen();
        void pollEvents();
        SDL_DisplayMode getDisplayMode();
        SDL_Window* getSDLWindow();
        SDL_GLContext  getGLContext();
    private:
        void initSDL();
        SDL_DisplayMode displayMode{};
        SDL_Window* window{nullptr};
        SDL_GLContext glContext{nullptr};
        i32 height{720};
        i32 width{1280};
        std::string title;
        SDL_Event sdlEvent{};
        bool bIsOpen{true};
    };
}

#endif //BATTLEBLAZE_WINDOW_H

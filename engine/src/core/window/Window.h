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
        Window(const std::string &title);
        ~Window();
        void swapBuffers();
        void close();
        void clear();
        SDL_DisplayMode getDisplayMode();
    private:
        SDL_DisplayMode displayMode;
        SDL_Window* window{nullptr};
        SDL_GLContext glContext;
        u32 height;
        u32 width;

    };
}

#endif //BATTLEBLAZE_WINDOW_H

//
// Created by cx9ps3 on 28.12.22.
//

#pragma once

#include <SDL3/SDL.h>
#include <string>
#include "../memory_pool/AllocatedObject.h"
#include "../application/Settings.h"

namespace core
{
    class Window : public mem::AllocatedObject
    {
    public:
        explicit Window(const Settings &settings);
        ~Window() override;
        void swapBuffers();
        void close();
        void clear();
        bool isOpen() const noexcept;
        i32 pollEvents(SDL_Event *sdlEvent);
        SDL_DisplayMode getDisplayMode() const noexcept;
        SDL_Window* getSDLWindow() const noexcept;
        SDL_GLContext  getGLContext() const noexcept;
    private:
        Settings settings;
        void initSDL();
        SDL_DisplayMode displayMode{};
        SDL_Window* window{nullptr};
        SDL_GLContext glContext{nullptr};
        i32 height{720};
        i32 width{1280};
        std::string title;
        bool bIsOpen{true};
        void setOpenGLVersion(const Settings::OpenGLSettings &openGlSettings);
    };
}


//
// Created by cx9ps3 on 25.05.2023.
//

#ifndef HEXENEDITOR_EDITORGUI_HPP
#define HEXENEDITOR_EDITORGUI_HPP

#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3_loader.h>
#include <backends/imgui_impl_opengl3.h>
#include <SDL3/SDL.h>
#include "Style.h"
#include "Dockspace.h"

namespace edit::gui
{
    class EditorGUI
    {
    public:
        explicit EditorGUI();
        explicit EditorGUI(SDL_Window* window,SDL_GLContext glContext);
        ~EditorGUI();
        void begin();
        void draw();
        void end();
        void processEvent(SDL_Event *event);
    private:
        Style style;
        ImGuiIO *io{nullptr};
        Dockspace dockspace;
    };
}



#endif //HEXENEDITOR_EDITORGUI_HPP

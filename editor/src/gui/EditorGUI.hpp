//
// Created by cx9ps3 on 25.05.2023.
//

#pragma once

#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3_loader.h>
#include <backends/imgui_impl_opengl3.h>
#include <SDL3/SDL.h>
#include "Style.hpp"
#include "Dockspace.hpp"
#include <gui/IGUI.hpp>
namespace hexen::editor::gui
{
class EditorGUI : public hexen::engine::gui::IGUI
    {
    public:
        /**
        * @class EditorGUI
        * @brief A class for handling the graphical user interface of the editor.
        *
        * This class provides functionality for managing the editor's graphical user interface.
        * It is responsible for creating and managing the main editor window, as well as handling
        * the OpenGL context for rendering the interface.
        */

        explicit EditorGUI();

        /**
        * @class EditorGUI
        * @brief The EditorGUI class represents the graphical user interface for the editor.
        *
        * The EditorGUI class provides functionalities to create and manage the editor's user interface,
        * including controls, windows, and menus.
        */

        explicit EditorGUI(SDL_Window* window,SDL_GLContext glContext);

        /**
        * @class EditorGUI
        * @brief The EditorGUI class represents the graphical user interface for the editor.
        *
        * This class helps with creating and managing the visual elements in the editor window.
        * It provides functionality for rendering the UI elements and handling user input.
        *
        * @note This class represents the graphical user interface and should be used in conjunction with other classes
        *       for the overall functionality of the editor.
        *
        */

        ~EditorGUI();

        /**
        * @brief Starts the GUI of editor.
        *
        * This function is used to start the GUI of editor. It is responsible for initializing
        * the necessary components and displaying the initial state of the editor interface.
        *
        */
        void begin();

        /**
        * @brief Draws the GUI for the EditorGUI class.
        *
        * This function is responsible for drawing the graphical user interface (GUI) for the EditorGUI class. It renders all
        * the elements on the screen required for the editor.
        *
        * @note This function does not return anything.
        *
        * @see EditorGUI
        *
        * The function should be called after all the necessary elements have been initialized on the screen.
        */


        void draw();

        /**
        * @brief Flags the end of the editor.
        *
        * This function is used to flag the end of the editor. It performs any necessary cleanup or finalization procedures before closing the editor.
        *
        * @par Usage
        * Call this function when you want to signal the end of the editor.
        *
        * @par Example
        *  ```
        * EditorGUI editor;
        * // code for initializing the editor
        * editor.end();
        * ```
        */

        void end();

        /**
        * @brief Processes SDL events in the editor GUI.
        *
        * This function handles the SDL events and performs relevant actions in the editor GUI. It uses the provided SDL_Event
        * parameter to determine the type of event and takes appropriate actions accordingly.
        *
        * @param event SDL event to be processed.
        */

        void processEvent(const SDL_Event &event) override;

        /**
        * @brief Retrieves the dockspace for the EditorGUI.
        *
        * This function returns the dockspace object that is utilized in the EditorGUI class
        *
        * @return The dockspace object used by the EditorGUI.
        */

        std::shared_ptr<Dockspace> getDockspace();

        /**
        * Binds the framebuffer for rendering in the Editor GUI.
        *
        * This function is responsible for binding the framebuffer before rendering
        * any GUI elements in the EditorGUI class.
        *
        * @note Make sure to call this function before rendering to the framebuffer.
        *
        * @see unbindFramebuffer()
        */

        void bindFramebuffer();

        /**
        * @brief Unbinds the currently bound framebuffer in the EditorGUI.
        *
        * This function unbinds the currently bound framebuffer in the EditorGUI. After calling this function,
        * the default framebuffer (usually the window) will be active again for rendering.
        *
        * Note that this function assumes that a framebuffer is already bound. If no framebuffer is currently bound,
        * calling this function will have no effect.
        *
        * @see bindFramebuffer()
        */

        void unbindFramebuffer();

    private:
        Style style;
        ImGuiIO *io{nullptr};
        std::shared_ptr<Dockspace> dockspace;
    };
}



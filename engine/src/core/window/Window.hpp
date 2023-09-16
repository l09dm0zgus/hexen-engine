//
// Created by cx9ps3 on 28.12.22.
//

#pragma once

#include <SDL3/SDL.h>
#include <string>
#include "../memory_pool/AllocatedObject.hpp"
#include "../application/Settings.hpp"

namespace hexen::engine::core
{
    class Window : public memory::AllocatedObject
    {
    public:

        /**
        * @class hexen::engine::core::Window
        * @brief The Window class represents a window in the game engine.
        *
        * The Window class is responsible for creating and managing a game window. It takes a reference to a Settings object
        * which contains the necessary configuration settings for the window.
        */

        explicit Window(const Settings &settings);

        /**
        * @class hexen::engine::core::Window
        * @brief The Window class represents a window in the game engine.
        *
        * The Window class provides functionality to create, destroy, and interact
        * with a window in the game engine. This class is responsible for managing
        * the operating system specific window, handling user input, and rendering
        * graphics.
        */

        ~Window() override;

        /**
        * @brief Swaps the front and back buffers of the window.
        *
        * This function is responsible for swapping the buffers of the window, which allows
        * the rendered content to be displayed on the screen. It should be called after
        * rendering the frame to update the display.
        *
        * @attention This function should only be called once per frame.
        */

        void swapBuffers();
        void close();

        /**
        * @brief Clears the contents of the Window.
        *
        * This function clears the contents of the Window by setting the background color
        * to the specified clear color.
        *
        */

        void clear();

        /**
        * @brief Resizes the window to the specified dimensions.
        *
        * This function resizes the window to the given width and height, in pixels.
        * Any contents rendered within the window will be adjusted accordingly.
        * As a consequence of resizing, the viewport and aspect ratio may also change.
        *
        */


        void resize();

        /**
        * @class hexen::engine::core::Window
        * @brief Represents the window used in the game engine.
        *
        * The Window class provides methods to retrieve the size of the window.
        */

        glm::vec2 getSize();

        /**
        * @brief Check if the window is open.
        *
        * A member function of the Window class in the hexen::engine::core namespace.
        * This function returns a boolean value indicating whether the window is open or not.
        *
        * @return True if the window is open, false otherwise.
        */

        [[nodiscard]] bool isOpen() const noexcept;


        i32 pollEvents(SDL_Event *sdlEvent);

        /**
        * @brief Get the current display mode of the window.
        *
        * This function returns the current display mode of the window, including information such as the width, height, bit depth, and refresh rate.
        * The returned display mode is in the hexen::engine::core::DisplayMode structure format.
        *
        * @return The current display mode of the window in hexen::engine::core::DisplayMode structure format.
        *
        * @note This function is guaranteed to be noexcept.
        */


        [[nodiscard]] SDL_DisplayMode getDisplayMode() const noexcept;

        /**
        * @brief Get the SDL window instance.
        *
        * This function is used to retrieve the SDL window created by the Window class.
        *
        * @return The SDL_Window pointer representing the window instance.
        */

        [[nodiscard]] SDL_Window* getSDLWindow() const noexcept;

        /**
        * @brief Retrieves the OpenGL context associated with the window.
        *
        * This method returns the OpenGL context that is associated with the window. The OpenGL context
        * is required for rendering and manipulation of OpenGL resources.
        *
        * @return A pointer to the OpenGL context associated with the window.
        * @note The returned OpenGL context may be nullptr if the context has not been created or if an error occurred.
        *
        */

        [[nodiscard]] SDL_GLContext  getGLContext() const noexcept;
    private:
        Settings settings;

        /**
        * @brief Initializes the SDL library for the Window class.
        *
        * This function initializes the Simple DirectMedia Layer (SDL) library
        * for the Window class, which provides a platform-independent interface
        * for rendering graphics and handling input events.
        *
        */

        void initSDL();
        SDL_DisplayMode displayMode{};
        SDL_Window* window{nullptr};
        SDL_GLContext glContext{nullptr};
        i32 height{720};
        i32 width{1280};
        std::string title;
        bool bIsOpen{true};

        /**
        * @class hexen::engine::core::Window
        * @brief The Window class handles all operations related to the application window.
        *
        * This class provides methods to create, configure, and manage the application window, including
        * setting the OpenGL version for rendering. The OpenGL version can be set using the provided OpenGLSettings
        * object, which contains information such as the major and minor version numbers, as well as other settings
        * like the depth and stencil buffer sizes.
        */

        void setOpenGLVersion(const Settings::OpenGLSettings &openGlSettings);
        void setIcon(const std::string &pathToIcon);

        SDL_Surface *icon{};
    };
}


//
// Created by cx9ps3 on 13.07.2023.
//

#pragma once

#include <core/Types.h>
#include <core/graphics/FrameBufferObject.h>
#include <core/graphics/texture/FrameBufferTexture.h>
#include "GUIWindow.h"

namespace edit::gui
{
    class FramebufferWindow : public GUIWindow
    {
    public:

        /**
        * @class FramebufferWindow
        * @brief Represents a window using a framebuffer for rendering.
        *
        * This class extends from the GUIWindow class and provides functionality
        * for creating and managing a window that uses a framebuffer for rendering.
        */

        explicit FramebufferWindow(const std::string &name);

        /**
        * @class edit::gui::FramebufferWindow
        * @brief The FramebufferWindow class represents a GUI window for rendering and editing.
        */

        void begin() override;

        /**
        * @brief Renders the GUI framebuffer window.
        *
        * This function is responsible for rendering the graphical user interface
        * (GUI) framebuffer window.
        *
        * @note This function does not return any value.
        */

        void draw() override;

        /**
        * @class FramebufferWindow
        * @brief Handles the rendering and display of a framebuffer window.
        */

        void end() override;

        /**
        * Binds the framebuffer associated with the GUI window.
        *
        * This function is responsible for binding the framebuffer associated with the
        * GUI window. It ensures that all subsequent rendering operations will be performed
        * on this specific framebuffer.
        *
        * @see FramebufferWindow
        */


        void bindFramebuffer();

        /**
        *
        * @brief Unbinds the currently bound framebuffer for this FramebufferWindow.
        *
        * This function unbinds the currently bound framebuffer for this FramebufferWindow instance.
        * It ensures that subsequent rendering operations are performed on the default framebuffer
        * provided by the underlying graphics library.
        *
        * \note The behavior of this function is dependent on the underlying graphics library being used.
        *
        * @sa edit::gui::FramebufferWindow::bindFramebuffer()
        */


        void unbindFramebuffer();
    private:

        /**
        * Clears the contents of the framebuffer window.
        *
        * This function clears the contents of the framebuffer window by filling it with
        * a specific color or by resetting it completely.
        *
        * The behavior of the function is determined by the implementation of the framebuffer
        * window class.
        *
        * Example usage:
        * @code{.cpp}
        * FramebufferWindow framebufferWindow;
        * framebufferWindow.clear();
        * @endcode
        *
        * @see FramebufferWindow
        */

        void clear();
        core::rend::FrameBufferObject frameBufferObject;
        std::unique_ptr<core::rend::FrameBufferTexture> frameBufferTexture;
    protected:

        /**
        * @class FramebufferWindow
        * @brief This class handles the rendering of the framebuffer window.
        *
        * This class provides a method to render the contents of the framebuffer window.
        * It is a member of the "edit::gui" namespace.
        */

        virtual void render();
    };
}

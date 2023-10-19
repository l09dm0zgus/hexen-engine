//
// Created by cx9ps3 on 13.07.2023.
//

#pragma once

#include "GUIWindow.hpp"
#include "graphics/buffers/GL/GLFrameBuffer.hpp"
#include <core/Types.hpp>
#include <core/graphics/texture/FrameBufferTexture.hpp>

namespace hexen::engine::graphics
{
	class FrameBuffer;
}

namespace hexen::editor::gui
{
	/**
    * @class FramebufferWindow
    * @brief Represents a window using a framebuffer for rendering.
    *
    * This class extends from the GUIWindow class and provides functionality
    * for creating and managing a window that uses a framebuffer for rendering.
    */

	class FramebufferWindow : public GUIWindow
	{
	public:
		/**
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
        * @brief Handles the rendering and display of a framebuffer window.
        */

		void end() override;

		/**
 		* @brief Renders the framebuffer content for the Hexen Editor GUI.
 		*
 		* This method clears the rendering pipeline with a specific color (represented as a glm vector).
 		* The color used is a specific shade of blue (R:0.39, G:0.58, B:0.93, A:1.0).
 		*
 		* This is done by passing an instance of engine::graphics::ClearCommand and the
 		* color vector to the RenderPipeline's executeCommandNow method.
		*/

		virtual void renderFramebufferContent();

	protected:
		std::shared_ptr<engine::graphics::FrameBuffer> framebuffer;
	};
}// namespace hexen::editor::gui

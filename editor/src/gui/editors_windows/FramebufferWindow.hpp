//
// Created by cx9ps3 on 13.07.2023.
//

#pragma once

#include "GUIWindow.hpp"
#include <core/Types.hpp>

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
 		* @brief Constructs a new FramebufferWindow object.
 		*
 		* This constructor takes a constant string reference as the name of the window, and a weak pointer to
 		* the parent Dockspace of this window. It adds the window to a profiler then initializes it.
 		*
 		* @param name A constant reference to a string representing the name of the window.
 		* @param parentDockspace A weak pointer referring to the parent Dockspace of this window.
 		*/

		explicit FramebufferWindow(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace);

		/**
 		* @brief Constructs a new FramebufferWindow object.
 		*
 		* This constructor takes a rvalue string as the name of the window, and a weak pointer to
 		* the parent Dockspace of this window. It adds the window to a profiler then initializes it.
 		*
 		* @param name A rvalue string representing the name of the window.
 		* @param parentDockspace A weak pointer referring to the parent Dockspace of this window.
 		*/

		explicit FramebufferWindow(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace);

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
	private:

		/**
 		* @brief This function initializes the FramebufferWindow by creating a new FrameBufferCommand and storing a pointer to the created FrameBuffer.
 		* Specifically, it implements the following steps:
 		* 1. Calls HEXEN_ADD_TO_PROFILE()
 		* 2. Defines a FrameBufferSpecification structure.
 		* 3. Adds a new FramebufferCommand to the RenderPipeline queue using the previously defined specification, and stores the returned ID.
 		* 4. Sets the framebuffer attribute of the class to the FrameBuffer referenced by the FramebufferCommand from the previous step.
 		*/

		void initialize();
	};
}// namespace hexen::editor::gui

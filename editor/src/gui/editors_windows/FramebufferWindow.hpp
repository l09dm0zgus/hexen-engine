//
// Created by cx9ps3 on 13.07.2023.
//

#pragma once

#include "GUIWindow.hpp"
#include <core/Types.hpp>

namespace hexen::engine::graphics
{
	class FrameBuffer;
	class RenderPipeline;
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

		virtual void renderFramebufferContent() = 0;

	protected:
		std::shared_ptr<engine::graphics::FrameBuffer> framebuffer;
		std::shared_ptr<engine::graphics::RenderPipeline> renderPipeline;

		/**
 		* @brief Adds content from the frame buffer to the GUI window
 		*
 		* This method adds the content of the frame buffer to the GUI window if the size of the window
 		* is more than 5x5. It adjusts the size of the frame buffer and the window as per the available content region.
 		* It then gets the color attachment object of the frame buffer as a texture, and adds it to the window
 		* draw list, effectively displaying the frame buffer content within the window.
 		*
		 * @note The method is part of the FramebufferWindow class in the hexen::editor::gui namespace.
 		*/

		void addFramebufferContentToWindow();

	private:

		/**
 		* @brief This function initializes the FramebufferWindow by creating a new FrameBufferCommand and storing a pointer to the created FrameBuffer.
 		* Specifically, it implements the following steps:
 		* 1. Calls HEXEN_ADD_TO_PROFILE()
		* 2. Create render pipeline.
 		* 3. Defines a FrameBufferSpecification structure.
 		* 4. Adds a new FramebufferCommand to the RenderPipeline queue using the previously defined specification, and stores the returned ID.
 		* 5. Sets the framebuffer attribute of the class to the FrameBuffer referenced by the FramebufferCommand from the previous step.
 		*/

		void initialize();
	};
}// namespace hexen::editor::gui

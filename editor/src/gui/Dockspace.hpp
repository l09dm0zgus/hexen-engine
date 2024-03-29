//
// Created by cx9ps3 on 09.06.2023.
//
#pragma once

#include "editors_windows/GUIWindow.hpp"
#include <core/Types.hpp>

namespace hexen::editor::gui
{
	class FramebufferWindow;

	/**
	* @class Dockspace
 	* @brief The Dockspace class.
 	* A class for managing GUI dockedWindows and their docking positions.
 	*/

	class Dockspace
	{
	public:
		/**
 		* @enum DockingPosition
 		* @brief An enumeration class that defines possible docking positions in the interface.
 		* @details Position can be up, down, left, right, center or none.
 		*
 		* @var DockingPosition::UP
 		* Docking position is up.
 		*
	 	* @var DockingPosition::DOWN
 		* Docking position is down.
 		*
 		* @var DockingPosition::LEFT
 		* Docking position is left.
 		*
 		* @var DockingPosition::RIGHT
 		* Docking position is right.
 		*
 		* @var DockingPosition::CENTER
 		* Docking position is at the center.
 		*
 		* @var DockingPosition::NONE
 		* Docking position is not defined.
 		*/

		enum class DockingPosition : hexen::engine::core::u8
		{
			UP,
			DOWN,
			LEFT,
			RIGHT,
			CENTER,
			NONE
		};

		/**
        * @brief This function draws the Dockspace GUI element.
        *
        * The draw() function is a member function of the Dockspace class
        * defined in the edit::gui namespace. It is responsible for rendering
        * the Dockspace GUI element on the screen.
        *
        * This function does not return any value.
        *
        *
        */

		void draw();

		/**
        * @brief Begins the rendering of a dockspace GUI element.
        *
        * This function starts the rendering of a dockspace GUI element. The dockspace is an
        * area where dockedWindows can be docked and organized. All docking-related operations should
        * be performed between a call to `begin()` and a call to `end()` for a dockspace.
        *
        *
        * @see end()
        */

		void begin();

		/**
        * @brief End the rendering of the dockspace.
        *
        * This function is used to complete the rendering of the dockspace in a GUI application.
        * It ensures that all the docked dockedWindows are properly rendered and handles any necessary
        * clean-up procedures.
        *
        * @see begin()
        */

		void end();

		/**
        * @brief Attaches a GUI window to a specific docking position.
        *
        * This function attaches the given GUI window to the specified docking position.
        * The GUI window is represented by a shared pointer to a GUIWindow object.
        * The docking position is defined by a DockingPosition object.
        *
        * @param guiWindow A shared pointer to the GUI window to attach.
        * @param dockingPosition The docking position to attach the GUI window to.
        *
        * @see GUIWindow
        * @see DockingPosition
        */

		void attachWindow(const std::shared_ptr<GUIWindow> &guiWindow, const DockingPosition &dockingPosition);

		void addFloatingWindow(const std::shared_ptr<GUIWindow> &guiWindow);

		/**
        * @brief Retrieves the window with the specified name.
        *
        * This function fetches the window object that matches the specified name.
        * The name should be a valid window name string.
        *
        * @param name The name of the window to retrieve.
        * @return The window object if found, otherwise nullptr.
        */

		std::shared_ptr<GUIWindow> getWindow(const std::string &name);

		/**
        * @brief Get the scene window associated with the dockspace.
        *
        * @return A pointer to the scene window, or nullptr if no scene window is associated.
        */

		std::shared_ptr<FramebufferWindow> getSceneWindow();

		/**
 		* @brief Gets a list of framebuffer dockedWindows.
 		*
 		* This function traverses the list of dockedWindows and dynamically casts each window
 		* to the type of `FramebufferWindow`. If the dynamic cast is successful, meaning
 		* that the window is an instance of `FramebufferWindow`, it adds the window to a
 		* new list. The function finally returns this new list of framebuffer dockedWindows.
 		*
 		* @return A list of shared pointers to framebuffer dockedWindows.
 		*/

		std::vector<std::shared_ptr<FramebufferWindow>> getListOfFramebufferWindows();

	private:
		/**
        * @brief Indicates whether the window is currently attached or not.
        *
        * This variable determines whether the window is currently attached to another window
        * or not. When the window is attached, it means that it is part of another window or a
        * larger UI hierarchy. When the window is not attached, it means that it is independent
        * and is the root of its own UI hierarchy.
        *
        * The value of this variable should be set to `true` if the window is attached, and `false`
        * if it is not attached.
        *
        */

		bool isAttachedWindow {true};

		/**
        * @brief Sets the dockedWindows in the dockspace.
        * This function is used to set the dockedWindows in the dockspace in the application's user interface.
        *
        * @param windowsInDockspace The dockedWindows to be set in the dockspace.
        * @return void
        *
        * @details The setWindowsInDockspace() function takes in a parameter `windowsInDockspace` which represents the dockedWindows to be set in the dockspace of the application's user interface. The function does not return any value.
        *
        */

		void setWindowsInDockspace();

		hexen::engine::core::u32 id;
		hexen::engine::core::u32 dockUpId {0};
		hexen::engine::core::u32 dockDownId {0};
		hexen::engine::core::u32 dockLeftId {0};
		hexen::engine::core::u32 dockRightId {0};

		/**
        * @brief Represents a collection of dockedWindows in a graphical user interface.
        *
        * The `dockedWindows` variable is a container that holds multiple window objects
        * within a graphical user interface. Each window object represents an
        * individual window in the interface.
        *
        * This variable is typically used to manage and manipulate the dockedWindows
        * within the interface, such as creating, closing, resizing, or moving
        * them.
        *
        */

		std::vector<std::shared_ptr<GUIWindow>> dockedWindows;
		std::vector<std::shared_ptr<GUIWindow>> floatingWindows;

		hexen::engine::core::HashTable<std::string, DockingPosition> dockingPositions;
	};
}// namespace hexen::editor::gui

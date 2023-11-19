//
// Created by cx9ps3 on 16.06.2023.
//

#pragma once

#include "DialogWindow.hpp"
#include <core/Types.hpp>

namespace hexen::editor::gui
{
	/**
 	* @class NewProjectWindow
 	* @brief Derived from the DialogWindow class.
 	*
 	* This class handles the activities related to a new project window.
 	*/

	class NewProjectWindow : public DialogWindow
	{
	private:
		/**
	 	* @enum ArraySizes
	 	* @brief contains size for different array components.
	 	*
	 	* The sizes defined here will be the maximum length that each of the array components can have.
	 	*/

		enum ArraySizes : engine::core::u64
		{
			PROJECT_NAME_SIZE = 256,	/**< The maximum size of project name */
			PATH_TO_PROJECT_SIZE = 512, /**< The maximum size of path to project */
		};
		char projectName[ArraySizes::PROJECT_NAME_SIZE] {'0'}; /**< Character array to store the project name*/
		char pathToProject[PATH_TO_PROJECT_SIZE] {'0'};		   /**< Character array to store the path to project */
		std::string projectPath;							   /**< Stores the project path */

		/**
	 	* @brief Clear the content of strings projectName and pathToProject
	 	*/

		void clearStrings();

		/**
	 	* @brief Draw the window content
	 	*
	 	* This function is override from the base DialogWindow class. It defines how content of the window should be drawn.
	 	*/

		void drawContent() override;

	public:
		/**
	 	* @brief Returns the project path
	 	*
	 	* @return std::string containing the project path
	 	*/

		std::string getProjectPath();

		/**
 		* @brief Constructor that takes a name and parent dockspace by reference.
 		*
 		* Constructs a new `NewProjectWindow` object with the given name and parent dockspace.
 		* The function also invokes macros to profile performance and clear strings.
 		*
 		* @param name The name of the new project window.
 		* @param parentDockspace The parent dockspace of the new project window.
 		*/

		NewProjectWindow(const std::string& name, const std::weak_ptr<Dockspace> &parentDockspace);

		/**
 		* @brief Constructor that takes a name and parent dockspace by move semantics.
 		*
 		* Constructs a new `NewProjectWindow` object by moving the given name and with the given parent dockspace.
 		* After moving the specified name, it becomes unusable in the caller context.
	 	* The function also invokes macros to prof
		* ile performance and clear strings.
 		*
 		* @param name The string to be moved to form the name of the new project window.
 		* @param parentDockspace The parent dockspace of the new project window.
 		*/

		NewProjectWindow(std::string&& name, const std::weak_ptr<Dockspace> &parentDockspace);
	};
}// namespace hexen::editor::gui

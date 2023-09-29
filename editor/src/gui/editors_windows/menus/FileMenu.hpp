//
// Created by cx9ps3 on 19.06.2023.
//

#pragma once

#include "../dialogs/NewProjectWindow.hpp"
#include "Menu.hpp"

namespace hexen::editor::gui
{
	/**
 	* @class FileMenu
 	* @brief A menu system for file management in a application.
 	* @details The FileMenu class provides various methods to interact with files,
 	*          such as opening, saving, and creating new files or projects.
 	*/

	class FileMenu : public Menu
	{
	private:
		/**
		 * @brief Displays main menu of the file system.
		 */

		void showMainMenu();

		/**
		 * @brief Shows the dialog for creating a new scene.
		 */

		void showNewScene();

		/**
		 * @brief Shows the dialog for opening an existing scene.
		 */

		void showOpenScene();

		/**
		 * @brief Shows the dialog for opening a recently opened scene.
		 */

		void showOpenRecentScene();

		/**
		 * @brief Shows the dialog for saving the current file.
		 */

		void showSave();

		/**
		 * @brief Shows the dialog for saving the current file with a different name.
		 */

		void showSaveAs();

		/**
		 * @brief Displays new project creation window.
		 */

		void showNewProject();

		/**
		 * @brief Displays open project dialog.
		 */

		void showOpenProject();

		/**
		 * @brief Allows saving current project.
		 */

		void showSaveProject();

		/**
		 * @brief Displays the file menu.
		 */

		void show();

		/**
		 * @brief Stops displaying the component.
		 */

		void showExit();

		/**
		 * @brief Callable object for saving a file.
		 */

		std::function<void()> saveFileCallback;

		/**
		 * @brief Callable object for "Save As" file action.
		 */

		std::function<void()> saveAsFileCallback;

		/**
		 * @brief Pointer to the NewProjectWindow.
		 */

		std::unique_ptr<NewProjectWindow> newProjectWindow;

		/**
		 * @brief Callable object for creating a new scene.
		 */

		std::function<void()> newSceneCallback;

		/**
		 * @brief Callable object for opening a scene.
		 */

		std::function<void()> openSceneCallback;

	public:
		/**
         * @brief Constructor that takes the menu name.
         * @param name The name of the menu.
         */
		explicit FileMenu(std::string name);

		/**
         * @brief Begin displaying menu.
         * @note This method should be overridden in a subclass.
         */
		void begin() override;

		/**
         * @brief Draw the menu on the screen.
         * @note This method should be overridden in a subclass.
         */
		void draw() override;

		/**
         * @brief Finish displaying menu.
         * @note This method should be overridden in a subclass.
         */
		void end() override;
	};

}// namespace hexen::editor::gui

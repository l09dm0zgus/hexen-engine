//
// Created by cx9ps3 on 10.06.2023.
//

#pragma once

#include "GUIWindow.hpp"
#include "menus/FileMenu.hpp"
#include "menus/Menu.hpp"

namespace hexen::editor::gui
{

	/**
 	* @class MainMenuBar
 	* @brief This class is an extension of the GUIWindow class and defines the main menu bar.
 	*
 	* The MainMenuBar class handles the creation and management of the main menu bar.
 	*/

	class MainMenuBar : public GUIWindow
	{
	private:
		/**
     	* @brief Private member representing a list of menus on the main menu bar.
     	*
     	* This vector contains shared pointers to the individual menus placed on the main menu bar.
     	*/

		std::vector<std::shared_ptr<Menu>> menus;

	public:
		/**
 		* @brief  Constructor for the MainMenuBar class.
 		*
 		* @param name String representing the name for the MainMenuBar instance.
 		* @param parentDockspace weak pointer to the parent Dockspace of the MenuBar.
 		*/

		MainMenuBar(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace);

		/**
 		* @brief  Constructor for the MainMenuBar class.
 		*
 		* @param name String (moved in this case) representing the name for the MainMenuBar instance.
 		* @param parentDockspace weak pointer to the parent Dockspace of the MenuBar.
 		*/

		MainMenuBar(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace);

		/**
     	* @brief A function that marks the beginning of the main menu bar.
     	*
     	* This function is used to signal the start of the main menu bar. It is overridden
     	* from the GUIWindow class.
     	*/

		void begin() override;

		/**
     	* @brief A function that is used to draw the main menu bar.
     	*
     	* This function is used to draw the main menu bar and its components on the screen.
     	* It is overridden from the GUIWindow class.
     	*/

		void draw() override;

		/**
     	* @brief A function that marks the end of the main menu bar.
     	*
     	* This function is used to signal the end of the main menu bar. It's overridden
     	* from the GUIWindow class.
     	*/

		void end() override;
	};

}// namespace hexen::editor::gui

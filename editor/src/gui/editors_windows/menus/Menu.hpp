//
// Created by cx9ps3 on 19.06.2023.
//

#pragma once

#include "../GUIWindow.hpp"
#include <functional>

namespace hexen::editor::gui
{
	/**
 	* @class Menu
 	* @brief A class representing a menu in a GUI window.
 	* It provides functionality to show menus and menu items.
 	* @extends GUIWindow
 	*/

	class Menu : public GUIWindow
	{
	public:

		/**
 		* @brief Constructs a Menu object with the given name and associated Dockspace object.
 		* @param name A constant string reference representing the name of the Menu object.
 		* @param parentDockspace A weak pointer to the associated Dockspace object.
 		*/

		Menu(const std::string& name, const std::weak_ptr<Dockspace> &parentDockspace);

		/**
 		* @brief Constructs a Menu object by moving the given name and linking it with the Dockspace object.
 		* @param name An rvalue string reference that will be moved to provide the name of the Menu object, avoiding copying.
 		* @param parentDockspace A weak pointer to the associated Dockspace object.
 		*/

		Menu(std::string&& name, const std::weak_ptr<Dockspace> &parentDockspace);

	protected:
		/**
		 * @brief Show a menu with a name and callback function.
		 *
		 * @param name The name of the menu to show.
		 * @param callback The function to call when the menu is clicked.
		 */

		void showMenu(const std::string &name, const std::function<void()> &callback);

		/**
		 * @brief Show a menu item with a name, shortcut text, and callback function.
		 *
		 * @param name The name of the menu item to show.
		 * @param shortcutText The shortcut text to display for the menu item.
		 * @param callback The function to call when the menu item is clicked.
		 */

		void showMenuItem(const std::string &name, const std::string &shortcutText, const std::function<void()> &callback);
	};
	;
}// namespace hexen::editor::gui

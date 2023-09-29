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
		 * @brief Construct a new Menu object.
		 *
		 * @param name The name of the menu.
		 */

		explicit Menu(std::string name);

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

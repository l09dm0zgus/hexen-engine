//
// Created by cx9ps3 on 15.06.2023.
//

#pragma once

#include <functional>
#include <imgui.h>
#include <map>

namespace hexen::editor::gui
{
	/**
 	* @class Shortcuts
 	* @brief A class responsible for handling keyboard shortcuts in the application.
 	*
 	* This class maps a list of ImGuiKeys to a standard function (a shortcut).
 	* The function is executed when the corresponding keys are pressed.
 	*/

	class Shortcuts
	{
	public:
		/**
     	* @typedef Keys
     	* @brief Shortcut for a list of ImGuiKeys.
     	*/
		using Keys = std::vector<ImGuiKey>;

		/**
     	* @brief Add a new shortcut to the list of handled shortcuts.
     	*
     	* This function takes a list of keys and a function, and maps the function to the key(s) in the internal
     	* data structure. The provided function is then executed when the corresponding keys are pressed.
     	*
     	* @param keys A list of keys that form a shortcut.
     	* @param callback The function to be executed when the shortcut is pressed.
     	*/

		static void addShortcut(const Keys &keys, const std::function<void()> &callback);

		/**
     	* @brief Process the input keyboard events.
     	*
     	* This function is meant to be called in the main event loop. It scans the keyboard state and triggers
     	* the functions associated with any pressed shortcuts.
     	*/

		static void processInput();

	private:
		/**
     	* @brief An associative container mapping key lists to their associated functions.
     	*
     	* The container uses a vector of ImGuiKeys as a key, and stores a function for each list of keys. This function
     	* is executed when its associated shortcut is pressed.
     	*/

		static std::map<Keys, std::function<void()>> shortcuts;
	};
}// namespace hexen::editor::gui

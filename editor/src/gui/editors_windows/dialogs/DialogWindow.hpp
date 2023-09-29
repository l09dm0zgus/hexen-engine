//
// Created by cx9ps3 on 27.06.2023.
//

#pragma once

#include "../GUIWindow.hpp"

namespace hexen::editor::gui
{
	/**
 	* @class DialogWindow
 	* @brief A class that represents a Dialog window.
 	* @extends GUIWindow
 	*/

	class DialogWindow : public GUIWindow
	{
	public:
		/**
     	* @brief List of possible actions for the DialogWindow class.
     	*/

		enum class Action : engine::core::i32
		{
			PRESSED_OK,	   ///< Represents the "OK" action.
			PRESSED_CANCEL,///< Represents the "Cancel" action.
			NONE,		   ///< Represents no action.
			FAILED		   ///< Represents a failed action.
		};

		/**
     	* @brief Construct a new Dialog Window object with a specific name.
     	* @param name The name of the new Dialog Window object.
     	*/

		explicit DialogWindow(std::string name);

		/**
     	* @brief Get the last action taken in the dialog window.
     	* @return The last action that was taken.
     	*/

		Action getLastAction();

		/**
     	* @brief Set the status of the dialog window.
     	* @param newIsOpen The new status of the dialog window.
     	*/

		void setOpen(bool newIsOpen);

		/**
     	* @brief A method that begins the dialog window.
     	*/

		void begin() override;

		/**
     	* @brief A method that ends the dialog window.
     	*/

		void end() override;

		/**
     	* @brief A method that draws the dialog window.
     	*/

		void draw() override;

	protected:
		/**
     	* @brief Set the action of the dialog window.
     	* @param newAction The new action of the dialog window.
     	*/

		void setAction(Action newAction);

		/**
     	* @brief Status of the DialogWindow, whether it's open or not.
     	*/

		bool isOpen = false;

		/**
     	* @brief Pure virtual method for drawing the content of the window.
     	* Derived classes will provide the actual implementation.
     	*/

		virtual void drawContent() = 0;

	private:
		/**
     	* @brief The action that was taken on the dialog window.
     	*/

		Action action;
	};
	;
}// namespace hexen::editor::gui

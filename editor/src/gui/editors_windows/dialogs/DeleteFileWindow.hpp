//
// Created by cx9ps3 on 26.06.2023.
//

#pragma once

#include "DialogWindow.hpp"
#include <filesystem>
namespace hexen::editor::gui
{
	/**
	 * @class DeleteFileWindow
 	* @brief This class provides a dialog window to delete a file
 	* @details It is a specialized dialog window used for deleting files in the HexenEngine project
 	*/

	class DeleteFileWindow : public DialogWindow
	{
	private:
		/**
    	* @brief The file's path that needs to be deleted
    	*/

		std::string path;

	protected:
		/**
    	* @brief Callback function triggered when file is to be deleted
    	*/

		std::function<void()> deleteCallback;

		/**
    	* @brief The text shown in the dialog box
    	*/

		std::string text = "Delete file :%s ?";

		/**
    	* @brief Draws the content of the dialog box
    	*/

		void drawContent() override;

	public:
		/**
    	* @brief Construct a DeleteFileWindow object with a given name
    	* @param name The name of the object
    	*/

		explicit DeleteFileWindow(std::string name);

		/**
    	* @brief Set the file's path that needs to be deleted
    	* @param pathToFile The file's path
    	*/

		void setPath(const std::string &pathToFile);
	};
}// namespace hexen::editor::gui

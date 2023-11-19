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
		* @memberof hexen::editor::gui::DeleteFileWindow
 		*
 		* @brief Constructor taking a name and a weak pointer to a dockspace.
 		*
 		* @param name The name of the file window.
 		* @param parentDockspace A weak pointer to the parent dockspace.
 		*/

		DeleteFileWindow(const std::string& name,const std::weak_ptr<Dockspace> &parentDockspace);

		/**
		* @memberof hexen::editor::gui::DeleteFileWindow
 		*
 		* @brief Move constructor taking a name and a weak pointer to a dockspace.
 		*
 		* @param name The name of the file window (rvalue reference).
 		* @param parentDockspace A weak pointer to the parent dockspace.
 		*/

		DeleteFileWindow(std::string&& name,const std::weak_ptr<Dockspace> &parentDockspace);

		/**
    	* @brief Set the file's path that needs to be deleted
    	* @param pathToFile The file's path
    	*/

		void setPath(const std::string &pathToFile);
	};
}// namespace hexen::editor::gui

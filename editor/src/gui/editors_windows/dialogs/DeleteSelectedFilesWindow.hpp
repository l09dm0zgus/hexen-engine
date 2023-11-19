//
// Created by cx9ps3 on 26.06.2023.
//

#pragma once

#include "DeleteFileWindow.hpp"

namespace hexen::editor::gui
{
	/**
 	* @class DeleteSelectedFilesWindow
 	* @brief A class to represent a window for deleting specifically selected files
 	* @details This class extends DeleteFileWindow. Provides a user interface to delete selected files from a list.
 	*/

	class DeleteSelectedFilesWindow : public DeleteFileWindow
	{
	private:
		/**
	     * @brief Paths of the selected files that are to be deleted.
     	*/

		std::vector<std::filesystem::path> paths;

		/**
     	* @brief Method to represent/delete selected files in the user interface.
     	*/

		void drawContent() override;

	public:

		/**
 		* @brief Constructor using const reference for DeleteSelectedFilesWindow.
 		*        This constructor is used when you have a variable that you dont need to change the value of.
 		*
 		* @param name const reference to a string, this string will be used to name the window.
 		* @param parentDockspace const reference to a weak_ptr pointing to Dockspace. This specifies the Dockspace the window is a child of.
 		*/

		DeleteSelectedFilesWindow(const std::string& name, const std::weak_ptr<Dockspace> &parentDockspace);

		/**
 		* @brief Constructor using rvalue reference for DeleteSelectedFilesWindow.
 		*        This constructor is used when you have a temporary object (rvalue) and want to avoid copying it.
 		*
 		* @param name rvalue reference to a string, this string will be used to name the window.
 		* @param parentDockspace const reference to a weak_ptr pointing to Dockspace. This specifies the Dockspace the window is a child of.
 		*/

		DeleteSelectedFilesWindow(std::string&& name, const std::weak_ptr<Dockspace>& parentDockspace);

		/**
     	* @brief Sets paths of the files which are to be deleted.
     	* @param selectedFiles Vector containing the paths of the selected files.
     	*/

		void setPaths(const std::vector<std::filesystem::path> &selectedFiles);
	};

}// namespace hexen::editor::gui

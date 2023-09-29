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
     	* @brief Constructs a DeleteSelectedFilesWindow object.
     	* @param name The name of the window.
     	*/

		explicit DeleteSelectedFilesWindow(std::string name);

		/**
     	* @brief Sets paths of the files which are to be deleted.
     	* @param selectedFiles Vector containing the paths of the selected files.
     	*/

		void setPaths(const std::vector<std::filesystem::path> &selectedFiles);
	};

}// namespace hexen::editor::gui

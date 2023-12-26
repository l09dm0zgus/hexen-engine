//
// Created by cx9ps3 on 26.06.2023.
//
#pragma once

#include "DialogWindow.hpp"
#include <filesystem>

namespace hexen::editor::gui
{
	/**
 	* @class CopyingFilesWindow
 	* @brief A dialog window designed for copying files in the HexenEngine project.
 	*
 	* This class is a special type of DialogWindow, where it handles file copying operations.
 	*
 	* @note Inherits from the DialogWindow class.
 	*/

	class CopyingFilesWindow : public DialogWindow
	{
	private:
		/** @brief Current path from which files are being copied */
		std::filesystem::path currentPath;

		/** @brief List of files that need to be copied */
		std::vector<std::filesystem::path> filesToCopy;

		/** @brief Message text for file copying */
		std::string text = "Copying file: %s";

		/** @brief Constant iterator pointing to the current file being copied */
		std::vector<std::filesystem::path>::const_iterator currentFileToCopy;

		/** @brief Number of files that have been copied so far */
		engine::core::i32 copiedFiles {0};

		/**
     	* @brief Function to draw the window content
     	*
     	* @note This is an overridden function from the parent DialogWindow class.
     	*/

		void drawContent() override;

		const std::vector<std::string> imagesExtensions{".gif", ".jpg" , ".jpeg" , ".png" , ".bmp", ".tga", ".psd", ".pic"};

	public:

		/**
 		* @brief Constructs a new instance of CopyingFilesWindow.
 		*
 		* @details This constructor moves the input string into the instance name and links this window to a parent Dockspace.
 		*
 		* @param name Unique identifier for this window. The name string is moved into the instance.
 		* @param parentDockspace A weak reference to a parent Dockspace, to embed this window.
 		*/

		CopyingFilesWindow(std::string &&name,const std::weak_ptr<Dockspace> &parentDockspace);

		/**
 		* @brief Constructs a new instance of CopyingFilesWindow.
 		*
 		* @details This constructor copies the input string into the instance name and links this window to a parent Dockspace.
 		*
 		* @param name Unique identifier for this window. The name string is directly passed to the instance.
 		* @param parentDockspace A weak reference to a parent Dockspace, to embed this window.
 		*/

		CopyingFilesWindow(const std::string &name,const std::weak_ptr<Dockspace> &parentDockspace);

		/**
     	* @brief Set the files to be copied
     	*
     	* @param files List of paths to the files to be copied
     	*/

		void setFilesToCopy(const std::vector<std::filesystem::path> &files);

		/**
     	* @brief Set the current path from which files are being copied
    	*
     	* @param currentPath The new current path
     	*/

		void setCurrentPath(const std::filesystem::path &currentPath);
	};
}// namespace hexen::editor::gui

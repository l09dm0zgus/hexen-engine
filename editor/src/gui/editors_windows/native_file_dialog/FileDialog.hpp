//
// Created by cx9ps3 on 14.06.2023.
//

#pragma once

#include "INativeFileDialog.hpp"

namespace hexen::editor::gui
{
	/**
 	* @class FileDialog
 	* @brief Provides functionality to interact with system file dialogues
 	*
 	* This class provides an interface to interact with the system dialogues
 	* that are used to open and save files.
 	*/

	class FileDialog
	{
	private:
		/**
     	* @brief A unique pointer to a native file dialog.
     	*/

		std::unique_ptr<INativeFileDialog> nativeFileDialog;

	public:
		/**
     	* @brief Default constructor.
     	*/
		FileDialog();

		/**
     	* @brief Opens the file dialog to choose a single file.
     	*
     	* @param filterList A list specifying the types of files that can be opened.
     	* @param defaultPath The initial directory shown in the dialog.
     	* @param pathToFile A reference where the path to the chosen file is stored.
     	* @return Status indicating the result of the operation.
     	*/

		INativeFileDialog::Status openDialog(const INativeFileDialog::FileFilter &filterList, const std::string &defaultPath, std::string &pathToFile);

		/**
     	* @brief Opens the file dialog to choose multiple files.
     	*
     	* @param filterList A list specifying the types of files that can be opened.
     	* @param defaultPath The initial directory shown in the dialog.
     	* @param pathToFiles A pointer to where the paths to the chosen files are stored.
     	* @return Status indicating the result of the operation.
     	*/

		INativeFileDialog::Status openDialog(const INativeFileDialog::FileFilter &filterList, const std::string &defaultPath, INativeFileDialog::PathSet *pathToFiles);

		/**
     	* @brief Opens the file dialog to save a file.
     	*
     	* @param filterList A list specifying the types of files that can be saved.
     	* @param defaultPath The initial directory shown in the dialog.
     	* @param pathToFile A reference where the path to the saved file is stored.
     	* @return Status indicating the result of the operation.
     	*/

		INativeFileDialog::Status saveDialog(const INativeFileDialog::FileFilter &filterList, const std::string &defaultPath, std::string &pathToFile);

		/**
     	* @brief Opens the file dialog to pick a directory.
     	*
     	* @param defaultPath The initial directory shown in the dialog.
     	* @param pathToFile A reference where the path to the picked directory is stored.
     	* @return Status indicating the result of the operation.
     	*/

		INativeFileDialog::Status pickDialog(const std::string &defaultPath, std::string &pathToFile);
	};
}// namespace hexen::editor::gui

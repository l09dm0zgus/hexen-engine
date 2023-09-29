//
// Created by cx9ps3 on 12.06.2023.
//

#pragma once

#include "INativeFileDialog.hpp"

#include <gtk/gtk.h>

namespace hexen::editor::gui
{
	/**
	* @class GTKFileDialog
	* @brief This class provides methods for handling file dialog operations with GTK+ GUI.
	* @inherits  INativeFileDialog
	*/

	class GTKFileDialog : public INativeFileDialog
	{
	public:
		/**
	 	* @brief Opens a file dialog with specified filter and default path.
	 	* @param filterList The file filters used in the dialog.
	 	* @param defaultPath The default path of the dialog.
	 	* @param pathToFile The selected file path(s) if successful.
	 	* @return Status of the operation.
	 	*/

		Status openDialog(const FileFilter &filterList, const std::string &defaultPath, std::string &pathToFile) override;

		/**
	 	* @brief Opens a file dialog with specified filter and default path, allows multiple file selection.
	 	* @param filterList The file filters used in the dialog.
	 	* @param defaultPath The default path of the dialog.
	 	* @param pathToFiles A pointer to a set of selected file paths if successful.
	 	* @return Status of the operation.
	 	*/

		Status openDialog(const FileFilter &filterList, const std::string &defaultPath, PathSet *pathToFiles) override;

		/**
	 	* @brief Opens a save file dialog with specified filter and default path.
	 	* @param filterList The file filters used in the dialog.
	 	* @param defaultPath The default path of the dialog.
	 	* @param pathToFile The selected file path if successful.
	 	* @return Status of the operation.
	 	*/

		Status saveDialog(const FileFilter &filterList, const std::string &defaultPath, std::string &pathToFile) override;

		/**
	 	* @brief Opens a file picker dialog with specified default path.
	 	* @param defaultPath The default path of the dialog.
	 	* @param pathToFile The selected file path if successful.
	 	* @return Status of the operation.
	 	*/

		Status pickDialog(const std::string &defaultPath, std::string &pathToFile) override;

	private:
		/**
	 	* @brief Adds filters to the dialog.
	 	* @param dialog The GTK+ dialog to which filters will be added.
	 	* @param fileFilter The filters to be added.
	 	*/

		void addFiltersToDialog(GtkWidget *dialog, const FileFilter &fileFilter);

		/**
	 	* @brief Sets the default path for the dialog.
	 	* @param dialog The GTK+ dialog for which the default path will be set.
	 	* @param defaultPath The default path to be set.
	 	*/

		void setDefaultPath(GtkWidget *dialog, const std::string &defaultPath);

		/**
	 	* @brief Allocates the path set with the selected files.
	 	* @param fileList The output of the GTK+ file dialog.
	 	* @param pathSet The set to be allocated.
	 	* @return Status of the operation.
	 	*/

		Status allocatePathSet(GSList *fileList, PathSet *pathSet);

		/**
	 	* @brief Waits for the file dialog cleanup to finish.
	 	*/

		void waitForCleanUp();
	};
}// namespace hexen::editor::gui

//
// Created by cx9ps3 on 14.06.2023.
//

#pragma once

#include "INativeFileDialog.hpp"

namespace hexen::editor::gui
{
	class FileDialog
	{
	private:
		std::unique_ptr<INativeFileDialog> nativeFileDialog;

	public:
		FileDialog();
		INativeFileDialog::Status openDialog(const INativeFileDialog::FileFilter &filterList, const std::string &defaultPath, std::string &pathToFile);
		INativeFileDialog::Status openDialog(const INativeFileDialog::FileFilter &filterList, const std::string &defaultPath, INativeFileDialog::PathSet *pathToFiles);
		INativeFileDialog::Status saveDialog(const INativeFileDialog::FileFilter &filterList, const std::string &defaultPath, std::string &pathToFile);
		INativeFileDialog::Status pickDialog(const std::string &defaultPath, std::string &pathToFile);
	};

}// namespace hexen::editor::gui

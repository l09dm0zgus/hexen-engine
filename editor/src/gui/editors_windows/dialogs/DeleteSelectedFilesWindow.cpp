//
// Created by cx9ps3 on 26.06.2023.
//

#include "DeleteSelectedFilesWindow.hpp"

hexen::editor::gui::DeleteSelectedFilesWindow::DeleteSelectedFilesWindow(std::string name) : DeleteFileWindow(std::move(name))
{
	text = "Delete this selected files?";
}

void hexen::editor::gui::DeleteSelectedFilesWindow::setPaths(const std::vector<std::filesystem::path> &selectedFiles)
{
	paths = selectedFiles;
	deleteCallback = [this]()
	{
		for (const auto &path : paths)
		{
			std::filesystem::remove_all(path);
		}
	};
}

void hexen::editor::gui::DeleteSelectedFilesWindow::drawContent()
{
	DeleteFileWindow::drawContent();
}

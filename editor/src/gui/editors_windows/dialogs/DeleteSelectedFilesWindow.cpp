//
// Created by cx9ps3 on 26.06.2023.
//

#include "DeleteSelectedFilesWindow.hpp"

void hexen::editor::gui::DeleteSelectedFilesWindow::setPaths(const std::vector<std::filesystem::path> &selectedFiles)
{
	HEXEN_ADD_TO_PROFILE();
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
	HEXEN_ADD_TO_PROFILE();
	DeleteFileWindow::drawContent();
}

hexen::editor::gui::DeleteSelectedFilesWindow::DeleteSelectedFilesWindow(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace) : DeleteFileWindow(name, parentDockspace)
{
	HEXEN_ADD_TO_PROFILE();
	text = "Delete this selected files?";
}

hexen::editor::gui::DeleteSelectedFilesWindow::DeleteSelectedFilesWindow(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace) : DeleteFileWindow(std::move(name), parentDockspace)
{
	HEXEN_ADD_TO_PROFILE();
	text = "Delete this selected files?";
}

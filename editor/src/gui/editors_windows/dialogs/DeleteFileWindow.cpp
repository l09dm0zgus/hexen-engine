//
// Created by cx9ps3 on 26.06.2023.
//

#include "DeleteFileWindow.hpp"
#include <filesystem>
#include <iostream>

void hexen::editor::gui::DeleteFileWindow::setPath(const std::string &pathToFile)
{
	HEXEN_ADD_TO_PROFILE();
	path = pathToFile;

	deleteCallback = [this]()
	{
		std::filesystem::remove_all(std::filesystem::path(path));
	};
}

void hexen::editor::gui::DeleteFileWindow::drawContent()
{
	HEXEN_ADD_TO_PROFILE();
	ImGui::Text(text.c_str(), path.c_str());
	ImGui::SameLine();

	if (ImGui::Button("Delete"))
	{
		setAction(Action::PRESSED_OK);
		deleteCallback();
		ImGui::CloseCurrentPopup();
	}

	auto windowWidth = ImGui::GetWindowSize().x;
	ImGui::SetCursorPosX(windowWidth * 0.5f);
	ImGui::SameLine();

	if (ImGui::Button("Cancel"))
	{
		setAction(Action::PRESSED_CANCEL);
		ImGui::CloseCurrentPopup();
	}
}

hexen::editor::gui::DeleteFileWindow::DeleteFileWindow(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace) : DialogWindow(name, parentDockspace)
{
	HEXEN_ADD_TO_PROFILE();
}

hexen::editor::gui::DeleteFileWindow::DeleteFileWindow(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace) : DialogWindow(std::move(name), parentDockspace)
{
	HEXEN_ADD_TO_PROFILE();
}

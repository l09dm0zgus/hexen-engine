//
// Created by cx9ps3 on 26.06.2023.
//

#include "DeleteFileWindow.hpp"
#include <filesystem>
#include <iostream>

hexen::editor::gui::DeleteFileWindow::DeleteFileWindow(std::string name) : DialogWindow(std::move(name))
{
}
void hexen::editor::gui::DeleteFileWindow::setPath(const std::string &pathToFile)
{
	path = pathToFile;

	deleteCallback = [this]()
	{
		std::filesystem::remove_all(std::filesystem::path(path));
	};
}

void hexen::editor::gui::DeleteFileWindow::drawContent()
{
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

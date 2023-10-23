//
// Created by cx9ps3 on 09.06.2023.
//

#include "GUIWindow.hpp"

#include <utility>

hexen::editor::gui::GUIWindow::GUIWindow(std::string name) : name(std::move(name))
{
	HEXEN_ADD_TO_PROFILE()
	setWindowSize();
}

std::string hexen::editor::gui::GUIWindow::getName() const noexcept
{
	HEXEN_ADD_TO_PROFILE()
	return name;
}

void hexen::editor::gui::GUIWindow::setWindowSize()
{
	HEXEN_ADD_TO_PROFILE()
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
}

glm::vec2 hexen::editor::gui::GUIWindow::getSize() const noexcept
{
	HEXEN_ADD_TO_PROFILE()
	return size;
}

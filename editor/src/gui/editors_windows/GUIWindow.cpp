//
// Created by cx9ps3 on 09.06.2023.
//

#include "GUIWindow.hpp"

#include <utility>

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

hexen::editor::gui::GUIWindow::GUIWindow(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace) : parentDockspace(parentDockspace), name(std::move(name))
{
	HEXEN_ADD_TO_PROFILE()
	setWindowSize();
}

hexen::editor::gui::GUIWindow::GUIWindow(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace) : parentDockspace(parentDockspace), name(name)
{
	HEXEN_ADD_TO_PROFILE()
	setWindowSize();
}

//
// Created by cx9ps3 on 09.06.2023.
//

#include "GUIWindow.hpp"
#include <uuid/uuid.hpp>

#include <utility>

std::string hexen::editor::gui::GUIWindow::getName() const noexcept
{
	HEXEN_ADD_TO_PROFILE()
	return name;
}

glm::vec2 hexen::editor::gui::GUIWindow::getSize() const noexcept
{
	HEXEN_ADD_TO_PROFILE()
	return size;
}

hexen::editor::gui::GUIWindow::GUIWindow(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace) : parentDockspace(parentDockspace), name(std::move(name))
{
	HEXEN_ADD_TO_PROFILE();
	UUID = generateUUIDV4();
}

hexen::editor::gui::GUIWindow::GUIWindow(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace) : parentDockspace(parentDockspace), name(name)
{
	HEXEN_ADD_TO_PROFILE();
	UUID = generateUUIDV4();
}

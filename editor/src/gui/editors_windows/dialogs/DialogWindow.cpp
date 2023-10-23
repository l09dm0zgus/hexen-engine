//
// Created by cx9ps3 on 27.06.2023.
//

#include "DialogWindow.hpp"

hexen::editor::gui::DialogWindow::DialogWindow(std::string name) : GUIWindow(name)
{
	HEXEN_ADD_TO_PROFILE();
}

hexen::editor::gui::DialogWindow::Action hexen::editor::gui::DialogWindow::getLastAction()
{
	HEXEN_ADD_TO_PROFILE();
	auto result = action;
	action = Action::NONE;
	return result;
}

void hexen::editor::gui::DialogWindow::setAction(hexen::editor::gui::DialogWindow::Action newAction)
{
	HEXEN_ADD_TO_PROFILE();
	action = newAction;
}

void hexen::editor::gui::DialogWindow::setOpen(bool newIsOpen)
{
	HEXEN_ADD_TO_PROFILE();
	isOpen = newIsOpen;
}

void hexen::editor::gui::DialogWindow::begin()
{
	HEXEN_ADD_TO_PROFILE();
}

void hexen::editor::gui::DialogWindow::end()
{
	HEXEN_ADD_TO_PROFILE();
}

void hexen::editor::gui::DialogWindow::draw()
{
	HEXEN_ADD_TO_PROFILE();
	if (isOpen)
	{
		setSize(glm::vec2(615, 110));
		ImGui::OpenPopup(getName().c_str());
	}
	if (ImGui::BeginPopupModal(getName().c_str()))
	{
		isOpen = false;
		drawContent();
		ImGui::EndPopup();
	}
}

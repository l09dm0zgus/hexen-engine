//
// Created by cx9ps3 on 27.06.2023.
//

#include "DialogWindow.hpp"

hexen::editor::gui::DialogWindow::DialogWindow(std::string name) : GUIWindow(name) {

}

hexen::editor::gui::DialogWindow::Action hexen::editor::gui::DialogWindow::getLastAction()
{
    auto result = action;
    action = Action::NONE;
    return result;
}

void hexen::editor::gui::DialogWindow::setAction(hexen::editor::gui::DialogWindow::Action newAction)
{
    action = newAction;
}

void hexen::editor::gui::DialogWindow::setOpen(bool newIsOpen)
{
    isOpen = newIsOpen;
}

void hexen::editor::gui::DialogWindow::begin()
{

}

void hexen::editor::gui::DialogWindow::end()
{

}

void hexen::editor::gui::DialogWindow::draw()
{
    if(isOpen)
    {
        setSize(glm::vec2(615,110));
        ImGui::OpenPopup(getName().c_str());
    }
    if(ImGui::BeginPopupModal(getName().c_str()))
    {
        isOpen = false;
        drawContent();
        ImGui::EndPopup();
    }
}

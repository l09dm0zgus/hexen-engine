//
// Created by cx9ps3 on 27.06.2023.
//

#include "DialogWindow.h"

edit::gui::DialogWindow::DialogWindow(std::string name) : GUIWindow(name) {

}

edit::gui::DialogWindow::Action edit::gui::DialogWindow::getLastAction()
{
    auto result = action;
    action = Action::NONE;
    return result;
}

void edit::gui::DialogWindow::setAction(edit::gui::DialogWindow::Action newAction)
{
    action = newAction;
}

void edit::gui::DialogWindow::setOpen(bool newIsOpen)
{
    isOpen = newIsOpen;
}

void edit::gui::DialogWindow::begin()
{

}

void edit::gui::DialogWindow::end()
{

}

void edit::gui::DialogWindow::draw()
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

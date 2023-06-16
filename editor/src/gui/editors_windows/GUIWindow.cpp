//
// Created by cx9ps3 on 09.06.2023.
//

#include "GUIWindow.h"

#include <utility>

edit::gui::GUIWindow::GUIWindow(std::string name) : name(std::move(name))
{
    setWindowSize();
}

std::string edit::gui::GUIWindow::getName() const noexcept
{
    return name;
}

void edit::gui::GUIWindow::setWindowSize()
{
    ImGui::SetWindowSize(name.c_str(),ImVec2(size.x,size.y));
}

glm::vec2 edit::gui::GUIWindow::getSize() const noexcept
{
    return size;
}

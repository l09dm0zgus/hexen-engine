//
// Created by cx9ps3 on 09.06.2023.
//

#include "GUIWindow.hpp"

#include <utility>

hexen::editor::gui::GUIWindow::GUIWindow(std::string name) : name(std::move(name))
{
    setWindowSize();
}

std::string hexen::editor::gui::GUIWindow::getName() const noexcept
{
    return name;
}

void hexen::editor::gui::GUIWindow::setWindowSize()
{
    ImGui::SetNextWindowSize(ImVec2(size.x,size.y));
}

glm::vec2 hexen::editor::gui::GUIWindow::getSize() const noexcept
{
    return size;
}

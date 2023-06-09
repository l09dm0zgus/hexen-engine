//
// Created by cx9ps3 on 09.06.2023.
//

#include "GUIWindow.h"

#include <utility>

edit::gui::GUIWindow::GUIWindow(std::string name) : name(std::move(name))
{

}

std::string edit::gui::GUIWindow::getName()
{
    return name;
}

//
// Created by cx9ps3 on 10.06.2023.
//

#include "MainMenuBar.h"

#include <utility>
#include "menus/FileMenu.h"

edit::gui::MainMenuBar::MainMenuBar(std::string name) : GUIWindow(std::move(name))
{
    menus.push_back(core::mem::make_shared<FileMenu>("File"));
}

void edit::gui::MainMenuBar::begin()
{
    for(auto & menu : menus)
    {
        menu->begin();
    }
}

void edit::gui::MainMenuBar::draw()
{
    for(auto & menu : menus)
    {
        menu->draw();
    }
}

void edit::gui::MainMenuBar::end()
{
    for(auto & menu : menus)
    {
        menu->end();
    }
}

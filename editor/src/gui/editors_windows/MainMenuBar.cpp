//
// Created by cx9ps3 on 10.06.2023.
//

#include "MainMenuBar.h"

#include <utility>
#include "menus/FileMenu.h"

hexen::editor::gui::MainMenuBar::MainMenuBar(std::string name) : GUIWindow(std::move(name))
{
    menus.push_back(hexen::engine::core::memory::make_shared<FileMenu>("File"));
}

void hexen::editor::gui::MainMenuBar::begin()
{
    for(auto & menu : menus)
    {
        menu->begin();
    }
}

void hexen::editor::gui::MainMenuBar::draw()
{
    for(auto & menu : menus)
    {
        menu->draw();
    }
}

void hexen::editor::gui::MainMenuBar::end()
{
    for(auto & menu : menus)
    {
        menu->end();
    }
}

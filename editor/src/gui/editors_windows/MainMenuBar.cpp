//
// Created by cx9ps3 on 10.06.2023.
//

#include "MainMenuBar.hpp"

#include "menus/FileMenu.hpp"
#include <utility>

void hexen::editor::gui::MainMenuBar::begin()
{
	HEXEN_ADD_TO_PROFILE()
	for (auto &menu : menus)
	{
		menu->begin();
	}
}

void hexen::editor::gui::MainMenuBar::draw()
{
	HEXEN_ADD_TO_PROFILE()
	for (auto &menu : menus)
	{
		menu->draw();
	}
}

void hexen::editor::gui::MainMenuBar::end()
{
	HEXEN_ADD_TO_PROFILE()
	for (auto &menu : menus)
	{
		menu->end();
	}
}

hexen::editor::gui::MainMenuBar::MainMenuBar(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace) : GUIWindow(name, parentDockspace)
{
	HEXEN_ADD_TO_PROFILE()
	menus.push_back(hexen::engine::core::memory::make_shared<FileMenu>("File", parentDockspace));
}

hexen::editor::gui::MainMenuBar::MainMenuBar(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace) : GUIWindow(std::move(name), parentDockspace)
{
	HEXEN_ADD_TO_PROFILE()
	menus.push_back(hexen::engine::core::memory::make_shared<FileMenu>("File", parentDockspace));
}

//
// Created by cx9ps3 on 19.06.2023.
//

#include "Menu.hpp"

void hexen::editor::gui::Menu::showMenu(const std::string &name, const std::function<void()> &callback)
{
	HEXEN_ADD_TO_PROFILE();
	if (ImGui::BeginMenu(name.c_str()))
	{
		callback();
		ImGui::EndMenu();
	}
}

void hexen::editor::gui::Menu::showMenuItem(const std::string &name, const std::string &shortcutText, const std::function<void()> &callback)
{
	HEXEN_ADD_TO_PROFILE();
	if (ImGui::MenuItem(name.c_str(), shortcutText.c_str()))
	{
		callback();
	}
}

hexen::editor::gui::Menu::Menu(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace) : GUIWindow(name, parentDockspace)
{
	HEXEN_ADD_TO_PROFILE();
}

hexen::editor::gui::Menu::Menu(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace) : GUIWindow(std::move(name), parentDockspace)
{
	HEXEN_ADD_TO_PROFILE();
}

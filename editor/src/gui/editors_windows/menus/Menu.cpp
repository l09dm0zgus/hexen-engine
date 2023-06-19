//
// Created by cx9ps3 on 19.06.2023.
//

#include "Menu.h"

edit::gui::Menu::Menu(std::string name)  : GUIWindow(std::move(name))
{

}

void edit::gui::Menu::showMenu(const std::string &name, const std::function<void()> &callback)
{
    if(ImGui::BeginMenu(name.c_str()))
    {
        callback();
        ImGui::EndMenu();
    }
}

void edit::gui::Menu::showMenuItem(const std::string &name, const std::string &shortcutText, const std::function<void()> &callback)
{
    if(ImGui::MenuItem(name.c_str(), shortcutText.c_str()))
    {
        callback();
    }
}
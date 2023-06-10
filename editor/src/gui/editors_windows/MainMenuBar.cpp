//
// Created by cx9ps3 on 10.06.2023.
//

#include "MainMenuBar.h"
#include <imgui.h>
#include <iostream>

edit::gui::MainMenuBar::MainMenuBar(std::string name) : GUIWindow(std::move(name))
{

}

void edit::gui::MainMenuBar::begin()
{

}

void edit::gui::MainMenuBar::draw()
{
    showMainMenu();
}

void edit::gui::MainMenuBar::end()
{

}

void edit::gui::MainMenuBar::showMainMenu()
{
    if(ImGui::BeginMainMenuBar())
    {
        showFileMenu();
        ImGui::EndMainMenuBar();
    }
}

void edit::gui::MainMenuBar::showMenu(const std::string &name,const std::function<void()> &callback)
{
    if(ImGui::BeginMenu(name.c_str()))
    {
        callback();
        ImGui::EndMenu();
    }
}

void edit::gui::MainMenuBar::showMenuItem(const std::string &name,const std::string &hotkey,const std::function<void()> &callback)
{
    std::cout << "Hot key:" << hotkey << "\n";
    if(ImGui::MenuItem(name.c_str(),hotkey.c_str()))
    {
        callback();
    }
}

void edit::gui::MainMenuBar::showFileMenu()
{
    auto callback = [this]() {
        showNewScene();
        showOpenScene();
        showOpenRecentScene();
        ImGui::Separator();
        showNewProject();
        showOpenProject();
        showSaveProject();
        ImGui::Separator();
        showSave();
        showSaveAs();
    };
    showMenu("File",callback);
}

void edit::gui::MainMenuBar::showNewScene()
{
    auto callback = [this]() {

    };
    showMenuItem("New Scene","CTRL+N",callback);
}

void edit::gui::MainMenuBar::showOpenScene()
{
    auto callback = [this]() {

    };
    showMenuItem("Open Scene","Ctrl+O",callback);
}

void edit::gui::MainMenuBar::showOpenRecentScene()
{
    auto callback = [this]() {

    };
    showMenu("Open Recent Scene",callback);
}

void edit::gui::MainMenuBar::showSave()
{
    auto callback = [this]() {

    };
    showMenuItem("Save","CTRL+S",callback);
}

void edit::gui::MainMenuBar::showSaveAs()
{
    auto callback = [this]() {

    };
    showMenuItem("Save As...","CTRL+SHIFT+S",callback);
}

void edit::gui::MainMenuBar::showNewProject()
{
    auto callback = [this]() {

    };
    showMenuItem("New Project...", "",callback);
}

void edit::gui::MainMenuBar::showOpenProject()
{
    auto callback = [this]() {

    };
    showMenuItem("Open Project...", "",callback);
}

void edit::gui::MainMenuBar::showSaveProject()
{
    auto callback = [this]() {

    };
    showMenuItem("Save Project", "",callback);
}

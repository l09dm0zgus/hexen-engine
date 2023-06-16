//
// Created by cx9ps3 on 10.06.2023.
//

#include "MainMenuBar.h"
#include "Shortcuts.h"
#include "native_file_dialog/FileDialog.h"
#include <imgui.h>
#include <iostream>

edit::gui::MainMenuBar::MainMenuBar(std::string name) : GUIWindow(std::move(name))
{
    newProjectWindow = core::mem::make_unique<NewProjectWindow>("New Project");

    saveAsFileCallback = [](){

        FileDialog fileDialog;
        INativeFileDialog::FileFilter filter;
        filter.push_back({{"Images"},{"png;bmp;jpg;"}});
        std::string path;
        if(fileDialog.saveDialog(filter,"",path) == INativeFileDialog::Status::STATUS_OK)
        {
            std::cout << path << "\n";
        }
    };


    Shortcuts::addShortcut({ImGuiKey_LeftCtrl,ImGuiKey_LeftShift,ImGuiKey_S}, saveAsFileCallback);
}

void edit::gui::MainMenuBar::begin()
{
    newProjectWindow->begin();
}

void edit::gui::MainMenuBar::draw()
{
    showMainMenu();
    newProjectWindow->draw();
}

void edit::gui::MainMenuBar::end()
{
    newProjectWindow->end();
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

void edit::gui::MainMenuBar::showMenuItem(const std::string &name, const std::string &shortcutText, const std::function<void()> &callback)
{
    if(ImGui::MenuItem(name.c_str(), shortcutText.c_str()))
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

    showMenuItem("Save","CTRL+S",saveFileCallback);
}

void edit::gui::MainMenuBar::showSaveAs()
{
    showMenuItem("Save As...","CTRL+SHIFT+S",saveAsFileCallback);
}

void edit::gui::MainMenuBar::showNewProject()
{

    auto callback = [this] ()
    {
        newProjectWindow->setOpen(true);
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

//
// Created by cx9ps3 on 10.06.2023.
//

#include "MainMenuBar.h"
#include "Shortcuts.h"
#include "native_file_dialog/FileDialog.h"
#include "MessageBox.h"
#include <imgui.h>
#include <iostream>

edit::gui::MainMenuBar::MainMenuBar(std::string name) : GUIWindow(std::move(name))
{
    newProjectWindow = core::mem::make_unique<NewProjectWindow>("New Project");

    saveAsFileCallback = [](){

        FileDialog fileDialog;
        INativeFileDialog::FileFilter filter;
        std::string pathToProject;

        std::pair<std::string,std::string> allFiles , sceneFile;

        allFiles.first = "All files";
        allFiles.second = "all";

        sceneFile.first = "Scene";
        sceneFile.second = "hxscene;";

        filter.push_back(allFiles);
        filter.push_back(sceneFile);

        std::string path;
        if (fileDialog.saveDialog(filter, pathToProject, path) == INativeFileDialog::Status::STATUS_ERROR)
        {
            ImGuiMessageBox::add(std::string("Error!"),std::string("Failed to saving file"));
        }

    };

    saveFileCallback = [](){

    };

    newSceneCallback = [](){

    };

    openSceneCallback = []() {

        FileDialog fileDialog;
        INativeFileDialog::FileFilter filter;
        std::string pathToProject;
        filter.push_back({{"Scenes"},{"hxscene;"}});
        std::string path;
        if (fileDialog.openDialog(filter, pathToProject, path) == INativeFileDialog::Status::STATUS_ERROR)
        {
            ImGuiMessageBox::add(std::string("Error!"),std::string("Failed to select scene file!"));
        }

    };


    Shortcuts::addShortcut({ImGuiKey_LeftCtrl,ImGuiKey_S},saveFileCallback);
    Shortcuts::addShortcut({ImGuiKey_LeftCtrl,ImGuiKey_O},openSceneCallback);
    Shortcuts::addShortcut({ImGuiKey_LeftCtrl,ImGuiKey_N},newSceneCallback);
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
        ImGui::Separator();
        showExit();
    };
    showMenu("File",callback);
}

void edit::gui::MainMenuBar::showNewScene()
{

    showMenuItem("New Scene","CTRL+N",newSceneCallback);
}

void edit::gui::MainMenuBar::showOpenScene()
{

    showMenuItem("Open Scene","CTRL+O",openSceneCallback);
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

        FileDialog fileDialog;
        INativeFileDialog::FileFilter filter;
        std::string pathToProject;
        filter.push_back({{"Project"},{"hxproj;"}});
        std::string path;
        if (fileDialog.openDialog(filter, pathToProject, path) == INativeFileDialog::Status::STATUS_ERROR)
        {
            ImGuiMessageBox::add(std::string("Error!"),std::string("Failed to select project file!"));
        }
    };
    showMenuItem("Open Project...", "",callback);
}

void edit::gui::MainMenuBar::showSaveProject()
{
    auto callback = [this]() {

    };
    showMenuItem("Save Project", "",callback);
}

void edit::gui::MainMenuBar::showExit()
{
    auto callback = [this]() {

        exit(0);
    };
    showMenuItem("Exit", "",callback);
}

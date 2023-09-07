//
// Created by cx9ps3 on 19.06.2023.
//

#include "FileMenu.hpp"
#include "../Shortcuts.hpp"
#include "../native_file_dialog/FileDialog.hpp"
#include "../MessageBox.hpp"
#include "../../IconsFontAwesome5.hpp"
#include "../../../project/Project.hpp"
#include <imgui.h>

hexen::editor::gui::FileMenu::FileMenu(std::string name) : Menu(std::move(name))
{
    newProjectWindow = engine::core::memory::make_unique<NewProjectWindow>("New Project");

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

void hexen::editor::gui::FileMenu::begin()
{
    newProjectWindow->begin();
}

void hexen::editor::gui::FileMenu::draw()
{
    showMainMenu();
    newProjectWindow->draw();
}

void hexen::editor::gui::FileMenu::end()
{
    newProjectWindow->end();
}

void hexen::editor::gui::FileMenu::showMainMenu()
{
    if(ImGui::BeginMainMenuBar())
    {
        show();
        ImGui::EndMainMenuBar();
    }
}

void hexen::editor::gui::FileMenu::show()
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
    showMenu(getName(),callback);
}

void hexen::editor::gui::FileMenu::showNewScene()
{

    showMenuItem( ICON_FA_MAP " New Scene","CTRL+N",newSceneCallback);
}

void hexen::editor::gui::FileMenu::showOpenScene()
{

    showMenuItem( ICON_FA_FILE_IMPORT" Open Scene","CTRL+O",openSceneCallback);
}

void hexen::editor::gui::FileMenu::showOpenRecentScene()
{
    auto callback = [this]() {

    };
    showMenu(ICON_FA_FILE_IMPORT" Open Recent Scene",callback);
}

void hexen::editor::gui::FileMenu::showSave()
{

    showMenuItem(ICON_FA_SAVE" Save","CTRL+S",saveFileCallback);
}

void hexen::editor::gui::FileMenu::showSaveAs()
{
    showMenuItem(ICON_FA_FOLDER_OPEN " Save As...","CTRL+SHIFT+S",saveAsFileCallback);
}

void hexen::editor::gui::FileMenu::showNewProject()
{
    auto callback = [this] ()
    {
        newProjectWindow->setOpen(true);
    };
    showMenuItem(ICON_FA_FOLDER_OPEN " New Project...", "",callback);
}

void hexen::editor::gui::FileMenu::showOpenProject()
{
    auto callback = [this]() {

        FileDialog fileDialog;
        INativeFileDialog::FileFilter filter;
        std::string pathToProject;
        filter.push_back({{"Project"},{"hxproj;"}});
        std::string path;

        auto status = fileDialog.openDialog(filter, pathToProject, path);

        if ( status == INativeFileDialog::Status::STATUS_ERROR)
        {
            ImGuiMessageBox::add(std::string("Error!"),std::string("Failed to select project file!"));
        }
        else if (status == INativeFileDialog::Status::STATUS_OK)
        {
            Project::setCurrentProject(path);
        }
    };
    showMenuItem(ICON_FA_FILE" Open Project...", "",callback);
}

void hexen::editor::gui::FileMenu::showSaveProject()
{
    auto callback = [this]() {
        if(Project::getCurrentProject() != nullptr)
        {
            Project::getCurrentProject()->save();
        }
    };
    showMenuItem(ICON_FA_SAVE" Save Project", "",callback);
}

void hexen::editor::gui::FileMenu::showExit()
{
    auto callback = [this]() {

        exit(0);
    };
    showMenuItem(ICON_FA_WINDOW_CLOSE" Exit", "",callback);
}
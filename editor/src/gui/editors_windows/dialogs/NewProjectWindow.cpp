//
// Created by cx9ps3 on 16.06.2023.
//

#include "NewProjectWindow.h"
#include "imgui.h"
#include "../native_file_dialog/FileDialog.h"
#include <memory.h>
#include "../MessageBox.h"
#include "../../../project/Project.h"

edit::gui::NewProjectWindow::NewProjectWindow(std::string name) : DialogWindow(std::move(name))
{
    clearStrings();
}

std::string edit::gui::NewProjectWindow::getProjectPath()
{
    return projectPath;
}

void edit::gui::NewProjectWindow::clearStrings()
{
    memset(projectName,'\0',PROJECT_NAME_SIZE);
    memset(pathToProject,'\0',PATH_TO_PROJECT_SIZE);
}

void edit::gui::NewProjectWindow::drawContent()
{
    ImGui::Text("Project name:");
    ImGui::SameLine();
    ImGui::InputText("##Project name",projectName, PROJECT_NAME_SIZE);

    ImGui::Text("Project Location:");
    ImGui::SameLine();
    ImGui::InputText("##Project Location",pathToProject, PATH_TO_PROJECT_SIZE);
    ImGui::SameLine();

    if (ImGui::Button("Open..."))
    {
        FileDialog fileDialog;
        std::string path;
        auto status = fileDialog.pickDialog("",path);

        if(status == INativeFileDialog::Status::STATUS_ERROR)
        {
            ImGuiMessageBox::add(std::string("Error!"),std::string("Failed to pick folder"));
        }
        memcpy(pathToProject,path.c_str(),path.size());
    }

    auto windowWidth = ImGui::GetWindowSize().x;

    ImGui::SetCursorPosX(windowWidth * 0.5f);
    if (ImGui::Button("Ok"))
    {
        if (projectName[0] == '\0')
        {
            ImGuiMessageBox::add(std::string("Error!"),std::string("Project name cannot be empty!"));
            setAction(Action::FAILED);
        }
        else if (pathToProject[0] == '\0')
        {
            ImGuiMessageBox::add(std::string("Error!"),std::string("Project location cannot be empty!"));
            setAction(Action::FAILED);
        }
        else
        {
            Project::setCurrentProject(pathToProject,projectName);
            setAction(Action::PRESSED_OK);
            clearStrings();
            ImGui::CloseCurrentPopup();
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel"))
    {
        setAction(Action::PRESSED_CANCEL);
        ImGui::CloseCurrentPopup();
    }
}

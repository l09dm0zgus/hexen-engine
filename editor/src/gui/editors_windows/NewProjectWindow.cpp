//
// Created by cx9ps3 on 16.06.2023.
//

#include "NewProjectWindow.h"
#include <imgui.h>
#include "native_file_dialog/FileDialog.h"
#include <memory.h>
#include "MessageBox.h"
#include "../../project/Project.h"

void edit::gui::NewProjectWindow::draw()
{
    if(isOpen)
    {
        setSize(glm::vec2(615,110));
        ImGui::OpenPopup(getName().c_str());
    }
    if(ImGui::BeginPopupModal(getName().c_str()))
    {
        isOpen = false;

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
            }
            else if (pathToProject[0] == '\0')
            {
                ImGuiMessageBox::add(std::string("Error!"),std::string("Project location cannot be empty!"));
            }
            else
            {
                auto project = core::mem::make_shared<Project>(pathToProject,projectName);
                Project::setCurrentProject(project);

                ImGui::CloseCurrentPopup();
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

edit::gui::NewProjectWindow::NewProjectWindow(std::string name) : GUIWindow(std::move(name))
{
    memset(projectName,'\0',PROJECT_NAME_SIZE);
    memset(pathToProject,'\0',PATH_TO_PROJECT_SIZE);
}

void edit::gui::NewProjectWindow::setOpen(bool newIsOpen)
{
    this->isOpen = newIsOpen;
}

void edit::gui::NewProjectWindow::begin()
{

}

void edit::gui::NewProjectWindow::end()
{

}

std::string edit::gui::NewProjectWindow::getProjectPath()
{
    return projectPath;
}

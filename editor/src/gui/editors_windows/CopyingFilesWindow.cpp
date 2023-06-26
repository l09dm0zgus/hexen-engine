//
// Created by cx9ps3 on 26.06.2023.
//

#include "CopyingFilesWindow.h"
#include "MessageBox.h"

edit::gui::CopyingFilesWindow::CopyingFilesWindow(std::string name) : GUIWindow(std::move(name))
{

}

void edit::gui::CopyingFilesWindow::setOpen(bool newIsOpen)
{
    isOpen = newIsOpen;
}

void edit::gui::CopyingFilesWindow::begin()
{

}

void edit::gui::CopyingFilesWindow::end()
{

}

void edit::gui::CopyingFilesWindow::draw()
{
    if(isOpen)
    {
        setSize(glm::vec2(615,110));
        ImGui::OpenPopup(getName().c_str());
    }
    if(ImGui::BeginPopupModal(getName().c_str()))
    {
        isOpen = false;
        if(currentFileToCopy != filesToCopy.cend())
        {

            ImGui::Text(text.c_str(),currentFileToCopy->string().c_str());

            const ImU32 color = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
            const ImU32 background = ImGui::GetColorU32(ImGuiCol_Button);

            std::filesystem::copy(*currentFileToCopy,currentPath);
            ImGui::ProgressBar(static_cast<float>(copedFiles + 1 )/ static_cast<float>(filesToCopy.size()),ImVec2(0, 1));
            copedFiles++;
            currentFileToCopy++;
        }
        else
        {
            ImGui::CloseCurrentPopup();
        }
        if (ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void edit::gui::CopyingFilesWindow::setFilesToCopy(const std::vector<std::filesystem::path> &files)
{
    filesToCopy = files;
    copedFiles = 0;
    currentFileToCopy = filesToCopy.cbegin();
}

void edit::gui::CopyingFilesWindow::setCurrentPath(const std::filesystem::path &currentPath)
{
    this->currentPath = currentPath;
}

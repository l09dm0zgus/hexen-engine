//
// Created by cx9ps3 on 26.06.2023.
//

#include "CopyingFilesStatus.h"
#include "MessageBox.h"

edit::gui::CopyingFilesStatus::CopyingFilesStatus(std::string name) : GUIWindow(std::move(name))
{

}

void edit::gui::CopyingFilesStatus::setOpen(bool newIsOpen)
{
    isOpen = newIsOpen;
}

void edit::gui::CopyingFilesStatus::begin()
{

}

void edit::gui::CopyingFilesStatus::end()
{

}

void edit::gui::CopyingFilesStatus::draw()
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

            bufferingBar("##buffer_bar", 0.7f, ImVec2(getSize().x, 6), background, color);
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

void edit::gui::CopyingFilesStatus::setFilesToCopy(const std::vector<std::filesystem::path> &files)
{
    filesToCopy = files;
    currentFileToCopy = filesToCopy.cbegin();
}

void edit::gui::CopyingFilesStatus::setCurrentPath(const std::filesystem::path &currentPath)
{
    this->currentPath = currentPath;
}

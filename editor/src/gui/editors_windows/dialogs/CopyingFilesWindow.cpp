//
// Created by cx9ps3 on 26.06.2023.
//

#include "CopyingFilesWindow.hpp"
#include "../MessageBox.hpp"

hexen::editor::gui::CopyingFilesWindow::CopyingFilesWindow(std::string name) : DialogWindow(std::move(name))
{

}


void hexen::editor::gui::CopyingFilesWindow::setFilesToCopy(const std::vector<std::filesystem::path> &files)
{
    filesToCopy = files;
    copedFiles = 0;
    currentFileToCopy = filesToCopy.cbegin();
}

void hexen::editor::gui::CopyingFilesWindow::setCurrentPath(const std::filesystem::path &currentPath)
{
    this->currentPath = currentPath;
}

void hexen::editor::gui::CopyingFilesWindow::drawContent()
{
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
        setAction(Action::PRESSED_OK);
        ImGui::CloseCurrentPopup();
    }
    if (ImGui::Button("Cancel"))
    {
        setAction(Action::PRESSED_CANCEL);
        ImGui::CloseCurrentPopup();
    }
}


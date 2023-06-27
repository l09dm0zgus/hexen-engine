//
// Created by cx9ps3 on 26.06.2023.
//

#include "DeleteFileWindow.h"
#include <filesystem>
#include <iostream>

edit::gui::DeleteFileWindow::DeleteFileWindow(std::string name) : DialogWindow(std::move(name))
{

}
void edit::gui::DeleteFileWindow::setPath(const std::string &pathToFile)
{
    path = pathToFile;

    deleteCallback = [this]()
    {
        std::filesystem::remove_all(std::filesystem::path(path));
    };
}

void edit::gui::DeleteFileWindow::drawContent()
{
    ImGui::Text(text.c_str(),path.c_str());
    ImGui::SameLine();

    if (ImGui::Button("Delete"))
    {
        deleteCallback();
        setAction(Action::PRESSED_OK);
        ImGui::CloseCurrentPopup();
    }

    auto windowWidth = ImGui::GetWindowSize().x;
    ImGui::SetCursorPosX(windowWidth * 0.5f);
    ImGui::SameLine();

    if (ImGui::Button("Cancel"))
    {
        setAction(Action::PRESSED_CANCEL);
        ImGui::CloseCurrentPopup();
    }
}

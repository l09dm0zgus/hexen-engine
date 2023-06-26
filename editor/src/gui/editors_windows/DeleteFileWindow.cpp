//
// Created by cx9ps3 on 26.06.2023.
//

#include "DeleteFileWindow.h"
#include <filesystem>

edit::gui::DeleteFileWindow::DeleteFileWindow(std::string name) : GUIWindow(std::move(name))
{

}

void edit::gui::DeleteFileWindow::begin()
{

}

void edit::gui::DeleteFileWindow::setOpen(bool newIsOpen)
{
    isOpen = newIsOpen;
}

void edit::gui::DeleteFileWindow::end()
{

}

void edit::gui::DeleteFileWindow::draw()
{
    drawPopUp();
}

void edit::gui::DeleteFileWindow::drawPopUp()
{
    if(isOpen)
    {
        setSize(glm::vec2(615,110));
        ImGui::OpenPopup(getName().c_str());
    }
    if(ImGui::BeginPopupModal(getName().c_str()))
    {
        isOpen = false;
        ImGui::Text(text.c_str(),path.c_str());
        ImGui::SameLine();

        if (ImGui::Button("Delete"))
        {
            deleteCallback();
            ImGui::CloseCurrentPopup();
        }

        auto windowWidth = ImGui::GetWindowSize().x;
        ImGui::SetCursorPosX(windowWidth * 0.5f);
        ImGui::SameLine();

        if (ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void edit::gui::DeleteFileWindow::setPath(const std::string &pathToFile)
{
    path = pathToFile;

    deleteCallback = [this]()
    {
        std::filesystem::remove_all(std::filesystem::path(path));
    };
}

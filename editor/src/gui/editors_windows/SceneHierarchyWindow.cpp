//
// Created by cx9ps3 on 28.06.2023.
//

#include "SceneHierarchyWindow.h"

edit::gui::SceneHierarchyWindow::SceneHierarchyWindow(std::string name) : GUIWindow(std::move(name))
{
    setSize(glm::vec2(400,300));
}

void edit::gui::SceneHierarchyWindow::begin()
{

}

void edit::gui::SceneHierarchyWindow::draw()
{
    ImGui::Begin(getName().c_str(),&isOpen,ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_HorizontalScrollbar);
    for(core::i32 i = 0; i < 10; i++)
    {
        ImGui::PushID(i);
        bool isNodeOpened = ImGui::TreeNodeEx(std::to_string(i).c_str(),ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth);
        ImGui::PopID();
        if(isNodeOpened)
        {
            ImGui::TreePop();
        }
    }
    ImGui::End();
}

void edit::gui::SceneHierarchyWindow::end()
{

}

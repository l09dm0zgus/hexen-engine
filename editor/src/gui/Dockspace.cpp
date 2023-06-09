//
// Created by cx9ps3 on 09.06.2023.
//

#include "Dockspace.h"
#include <imgui.h>
#include <imgui_internal.h>

void edit::gui::Dockspace::draw()
{
    if(isAttachedWindow)
    {
        isAttachedWindow = false;
        setWindowsInDockspace();
    }
    for(auto& window : windows)
    {
        window->draw();
    }
}

void edit::gui::Dockspace::begin()
{
    for(auto& window : windows)
    {
        window->begin();
    }
}

void edit::gui::Dockspace::end()
{
    for(auto& window : windows)
    {
        window->end();
    }
}

void edit::gui::Dockspace::setWindowsInDockspace()
{
    id = ImGui::DockSpaceOverViewport();
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::DockBuilderRemoveNode(id); // clear any previous layout
    ImGui::DockBuilderAddNode(id, ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(id, viewport->Size);

    dockUpId = ImGui::DockBuilderSplitNode(id,ImGuiDir_Up,0.2f, nullptr,&id);
    dockDownId = ImGui::DockBuilderSplitNode(id,ImGuiDir_Down,0.25f, nullptr,&id);
    dockLeftId = ImGui::DockBuilderSplitNode(id,ImGuiDir_Left,0.2f, nullptr,&id);
    dockRightId = ImGui::DockBuilderSplitNode(id,ImGuiDir_Right,0.15f, nullptr,&id);


    for(auto &dockingPosition : dockingPositions)
    {
        switch (dockingPosition.value)
        {
            case DockingPosition::DOWN:
                ImGui::DockBuilderDockWindow( dockingPosition.key.c_str(), dockDownId);
                break;
            case DockingPosition::UP:
                ImGui::DockBuilderDockWindow( dockingPosition.key.c_str(), dockUpId);
                break;
            case DockingPosition::LEFT:
                ImGui::DockBuilderDockWindow( dockingPosition.key.c_str(), dockLeftId);
                break;
            case DockingPosition::RIGHT:
                ImGui::DockBuilderDockWindow( dockingPosition.key.c_str(), dockRightId);
                break;

        }
    }
    ImGui::DockBuilderFinish(id);
}

void edit::gui::Dockspace::attachWindow(std::shared_ptr<GUIWindow> guiWindow,const DockingPosition &dockingPosition)
{
    windows.push_back(guiWindow);
    dockingPositions.set(guiWindow->getName(),dockingPosition);
    isAttachedWindow = true;
}

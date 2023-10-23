//
// Created by cx9ps3 on 09.06.2023.
//

#include "Dockspace.hpp"
#include "editors_windows/SceneWindow.hpp"
#include <SDL_log.h>
#include <imgui.h>
#include <imgui_internal.h>


void hexen::editor::gui::Dockspace::draw()
{
	HEXEN_ADD_TO_PROFILE()
	id = ImGui::DockSpaceOverViewport();
	if (isAttachedWindow)
	{
		isAttachedWindow = false;
		setWindowsInDockspace();
	}
	for (auto &window : windows)
	{
		window->draw();
	}
}


void hexen::editor::gui::Dockspace::begin()
{
	HEXEN_ADD_TO_PROFILE()
	for (auto &window : windows)
	{
		window->begin();
	}
}

void hexen::editor::gui::Dockspace::end()
{
	HEXEN_ADD_TO_PROFILE()
	for (auto &window : windows)
	{
		window->end();
	}
}

void hexen::editor::gui::Dockspace::setWindowsInDockspace()
{
	HEXEN_ADD_TO_PROFILE()
	ImGuiViewport *viewport = ImGui::GetMainViewport();

	ImGui::DockBuilderRemoveNode(id);// clear any previous layout
	ImGui::DockBuilderAddNode(id, ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_DockSpace);
	ImGui::DockBuilderSetNodeSize(id, viewport->Size);

	dockUpId = ImGui::DockBuilderSplitNode(id, ImGuiDir_Up, 0.2f, nullptr, &id);
	dockDownId = ImGui::DockBuilderSplitNode(id, ImGuiDir_Down, 0.25f, nullptr, &id);
	dockLeftId = ImGui::DockBuilderSplitNode(id, ImGuiDir_Left, 0.2f, nullptr, &id);
	dockRightId = ImGui::DockBuilderSplitNode(id, ImGuiDir_Right, 0.15f, nullptr, &id);

	for (auto &dockingPosition : dockingPositions)
	{
		switch (dockingPosition.value)
		{
			case DockingPosition::DOWN:
				ImGui::DockBuilderDockWindow(dockingPosition.key.c_str(), dockDownId);
				break;
			case DockingPosition::UP:
				ImGui::DockBuilderDockWindow(dockingPosition.key.c_str(), dockUpId);
				break;
			case DockingPosition::LEFT:
				ImGui::DockBuilderDockWindow(dockingPosition.key.c_str(), dockLeftId);
				break;
			case DockingPosition::RIGHT:
				ImGui::DockBuilderDockWindow(dockingPosition.key.c_str(), dockRightId);
				break;
			case DockingPosition::CENTER:
				ImGui::DockBuilderDockWindow(dockingPosition.key.c_str(), id);
				break;
			default:
				break;
		}
	}
	ImGui::DockBuilderFinish(id);
}

void hexen::editor::gui::Dockspace::attachWindow(std::shared_ptr<GUIWindow> guiWindow, const DockingPosition &dockingPosition)
{
	HEXEN_ADD_TO_PROFILE()
	windows.push_back(guiWindow);
	dockingPositions.set(guiWindow->getName(), dockingPosition);
	isAttachedWindow = true;
}

std::shared_ptr<hexen::editor::gui::GUIWindow> hexen::editor::gui::Dockspace::getWindow(const std::string &name)
{
	HEXEN_ADD_TO_PROFILE()
	auto it = std::find_if(windows.begin(), windows.end(), [name = name](const auto &window)
			{ return window->getName() == name; });

	if (it != windows.end())
	{
		return *it;
	}
	else
	{
		SDL_Log("Failed to find editor window\n");
		return nullptr;
	}
}


std::shared_ptr<hexen::editor::gui::FramebufferWindow> hexen::editor::gui::Dockspace::getSceneWindow()
{
	HEXEN_ADD_TO_PROFILE()
	auto sceneWindow = getWindow("Scene");
	return std::dynamic_pointer_cast<FramebufferWindow>(sceneWindow);
}

std::vector<std::shared_ptr<hexen::editor::gui::FramebufferWindow>> hexen::editor::gui::Dockspace::getListOfFramebufferWindows()
{
	HEXEN_ADD_TO_PROFILE()
	std::vector<std::shared_ptr<FramebufferWindow>> frameBufferWindows;
	for(auto &window : windows)
	{
		auto framebufferWindow = std::dynamic_pointer_cast<FramebufferWindow>(window);
		if(framebufferWindow != nullptr)
		{
			frameBufferWindows.push_back(framebufferWindow);
		}
	}
	return frameBufferWindows;
}

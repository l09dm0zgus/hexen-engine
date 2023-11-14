//
// Created by cx9ps3 on 27.06.2023.
//

#include "AssetsIcon.hpp"
#include "AssetsWindow.hpp"
#include <misc/cpp/imgui_stdlib.h>

hexen::editor::gui::AssetsWindow *hexen::editor::gui::AssetIcon::assetsWindow {nullptr};

hexen::editor::gui::AssetIcon::AssetIcon(const std::filesystem::path &pathToAsset, const std::function<void(const std::filesystem::path &)> &newCallback, hexen::editor::gui::AssetsWindow *newAssetsWindow, hexen::engine::core::u32 textureId) : textureId(textureId) , callback(newCallback)
{
	HEXEN_ADD_TO_PROFILE();
	name = pathToAsset.filename();
	pathToFile = pathToAsset.string();
	fileName = name.string();
	assetsWindow = newAssetsWindow;
}

void hexen::editor::gui::AssetIcon::setSize(const glm::vec2 &newSize)
{
	HEXEN_ADD_TO_PROFILE();
	size = newSize;
}

void hexen::editor::gui::AssetIcon::draw()
{
	HEXEN_ADD_TO_PROFILE();
	isCtrlPressed = ImGui::IsKeyDown(ImGuiKey_LeftCtrl);
	ImGui::PushStyleColor(ImGuiCol_Button, color);
	isClicked = ImGui::ImageButton(name.string().c_str(), reinterpret_cast<ImTextureID>(textureId), ImVec2(size.x, size.y));
	setAssetWindowHoveredIcon();

	createDragAndDropSource();

	selectingFiles();

	createDragAndDropTarget();

	ImGui::PopStyleColor();

	showFilename();
	setAssetWindowHoveredIcon();

	ImGui::NextColumn();
}

void hexen::editor::gui::AssetIcon::createDragAndDropSource()
{
	HEXEN_ADD_TO_PROFILE();
	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload(PAYLOAD_NAME.data(), pathToFile.c_str(), (pathToFile.size() + 1) * sizeof(char));
		ImGui::EndDragDropSource();
	}
}

void hexen::editor::gui::AssetIcon::createDragAndDropTarget()
{
	HEXEN_ADD_TO_PROFILE();
	if (ImGui::BeginDragDropTarget())
	{
		if (auto payload = ImGui::AcceptDragDropPayload(PAYLOAD_NAME.data()))
		{
			auto draggedFilePath = (char *) payload->Data;
			std::filesystem::path fileToMove(draggedFilePath);
			if (std::filesystem::is_directory(pathToFile))
			{
				std::filesystem::rename(fileToMove, pathToFile / fileToMove.filename());
				assetsWindow->refresh();
			}
		}
		ImGui::EndDragDropTarget();
	}
}

void hexen::editor::gui::AssetIcon::showFilename()
{
	HEXEN_ADD_TO_PROFILE();
	if (!isEditingName)
	{
		auto text = name.string().c_str();
		ImGui::TextWrapped(text);
		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			isEditingName = true;
		}
	}
	else
	{
		if (ImGui::InputText("##", &fileName, ImGuiInputTextFlags_EnterReturnsTrue))
		{
			auto path = std::filesystem::path(pathToFile).parent_path();
			std::filesystem::rename(pathToFile, path / fileName);
			assetsWindow->refresh();
			isEditingName = false;
		}
	}
}

void hexen::editor::gui::AssetIcon::selectingFiles()
{
	HEXEN_ADD_TO_PROFILE();
	if (isCtrlPressed && isClicked)
	{
		color = ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered];
		assetsWindow->selectedFiles.emplace_back(pathToFile);
	}
	else if (isClicked)
	{
		color = {0.0f, 0.0f, 0.0f, 0.0f};
		assetsWindow->selectedFiles.clear();
		callback(pathToFile);
	}
	else if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	{
		color = {0.0f, 0.0f, 0.0f, 0.0f};
		assetsWindow->selectedFiles.clear();
	}
}

std::string hexen::editor::gui::AssetIcon::getPath() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return pathToFile;
}

void hexen::editor::gui::AssetIcon::setAssetWindowHoveredIcon()
{
	HEXEN_ADD_TO_PROFILE();
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenBlockedByPopup))
	{
		assetsWindow->currentHoveredIcon = this;
	}
}

void hexen::editor::gui::AssetIcon::renameFile()
{
	HEXEN_ADD_TO_PROFILE();
	isEditingName = true;
}

void hexen::editor::gui::AssetIconCallbacks::addCallback(const std::string &assetExtension, const std::function<void(const std::filesystem::path &)> &callback)
{
	HEXEN_ADD_TO_PROFILE();
	callbacks[assetExtension] = callback;
}

std::function<void(const std::filesystem::path &)> &hexen::editor::gui::AssetIconCallbacks::getCallback(const std::string &assetExtension)
{
	HEXEN_ADD_TO_PROFILE();
	return callbacks[assetExtension];
}

//
// Created by cx9ps3 on 27.06.2023.
//

#include "AssetsIcon.hpp"
#include "AssetsWindow.hpp"
#include <misc/cpp/imgui_stdlib.h>

std::unique_ptr<hexen::engine::graphics::gl::Texture> hexen::editor::gui::AssetIcon::fileIcon;
std::unique_ptr<hexen::engine::graphics::gl::Texture> hexen::editor::gui::AssetIcon::animationFileIcon;
std::unique_ptr<hexen::engine::graphics::gl::Texture> hexen::editor::gui::AssetIcon::entityFileIcon;
std::unique_ptr<hexen::engine::graphics::gl::Texture> hexen::editor::gui::AssetIcon::folderIcon;
std::unique_ptr<hexen::engine::graphics::gl::Texture> hexen::editor::gui::AssetIcon::sceneFileIcon;
std::unique_ptr<hexen::engine::graphics::gl::Texture> hexen::editor::gui::AssetIcon::soundFileIcon;
std::unique_ptr<hexen::engine::graphics::gl::Texture> hexen::editor::gui::AssetIcon::tilesetFileIcon;
hexen::editor::gui::AssetsWindow *hexen::editor::gui::AssetIcon::assetsWindow {nullptr};
hexen::engine::core::HashTable<hexen::engine::core::u32, std::string> hexen::editor::gui::AssetIcon::engineFileExtensions;

hexen::editor::gui::AssetIcon::AssetIcon(const std::filesystem::directory_entry &path, AssetsWindow *newAssetsWindow)
{

	name = path.path().filename();
	pathToFile = path.path().string();
	fileName = name.string();

	assetsWindow = newAssetsWindow;

	if (fileIcon == nullptr)
	{
		//use static class members for memory optimization

		folderIcon = hexen::engine::core::memory::make_unique<hexen::engine::graphics::gl::Texture>(pathToFolderIcon);
		soundFileIcon = hexen::engine::core::memory::make_unique<hexen::engine::graphics::gl::Texture>(pathToSoundFileIcon);
		fileIcon = hexen::engine::core::memory::make_unique<hexen::engine::graphics::gl::Texture>(pathToFileIcon);
		sceneFileIcon = hexen::engine::core::memory::make_unique<hexen::engine::graphics::gl::Texture>(pathToSceneFileIcon);
		animationFileIcon = hexen::engine::core::memory::make_unique<hexen::engine::graphics::gl::Texture>(pathToAnimationFileIcon);
		tilesetFileIcon = hexen::engine::core::memory::make_unique<hexen::engine::graphics::gl::Texture>(pathToTilesetFileIcon);
		entityFileIcon = hexen::engine::core::memory::make_unique<hexen::engine::graphics::gl::Texture>(pathToEntityFileIcon);

		engineFileExtensions.set(sceneFileIcon->getId(), ".hxscene");
		engineFileExtensions.set(animationFileIcon->getId(), ".hxanim");
		engineFileExtensions.set(tilesetFileIcon->getId(), ".hxtile");
		engineFileExtensions.set(entityFileIcon->getId(), ".hxentity");
	}

	if (path.is_directory())
	{
		textureId = folderIcon->getId();
		callback = [this](const std::string &path)
		{
			auto filename = std::filesystem::path(path).filename().string();
			assetsWindow->directoryList.push_back(filename);
			assetsWindow->currentPath = assetsWindow->currentPath / filename;
			assetsWindow->refresh();
		};
	}
	else
	{
		auto extension = name.extension().string();
		auto isImage = std::find(imageFileExtensions.cbegin(), imageFileExtensions.cend(), extension);
		auto isAudio = std::find(soundFileExtensions.cbegin(), soundFileExtensions.cend(), extension);
		auto isEngineFile = std::find_if(engineFileExtensions.begin(), engineFileExtensions.end(), [&extension](const auto &keyValue)
				{ return keyValue.value == extension; });

		if (isImage != imageFileExtensions.cend())
		{
			this->callback = [this](auto &fullPathToFile) {

			};

			imageFileIcon = hexen::engine::core::memory::make_unique<hexen::engine::graphics::gl::Texture>(path.path().string());
			textureId = imageFileIcon->getId();
		}
		else if (isAudio != soundFileExtensions.cend())
		{
			this->callback = [this](auto &fullPathToFile) {

			};

			textureId = soundFileIcon->getId();
		}
		else if (isEngineFile != engineFileExtensions.cend())
		{
			this->callback = [this](auto &fullPathToFile) {

			};

			textureId = isEngineFile->key;
		}
		else
		{
			this->callback = [this](auto &fullPathToFile) {

			};

			textureId = fileIcon->getId();
		}
	}
}

void hexen::editor::gui::AssetIcon::setSize(const glm::vec2 &newSize)
{
	size = newSize;
}

void hexen::editor::gui::AssetIcon::draw()
{
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
	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload(PAYLOAD_NAME.c_str(), pathToFile.c_str(), (pathToFile.size() + 1) * sizeof(char));
		ImGui::EndDragDropSource();
	}
}

void hexen::editor::gui::AssetIcon::createDragAndDropTarget()
{
	if (ImGui::BeginDragDropTarget())
	{
		if (auto payload = ImGui::AcceptDragDropPayload(PAYLOAD_NAME.c_str()))
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
	return pathToFile;
}

void hexen::editor::gui::AssetIcon::setAssetWindowHoveredIcon()
{
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenBlockedByPopup))
	{
		assetsWindow->currentHoveredIcon = this;
	}
}

void hexen::editor::gui::AssetIcon::renameFile()
{
	isEditingName = true;
}

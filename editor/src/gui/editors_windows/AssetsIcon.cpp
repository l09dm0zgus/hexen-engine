//
// Created by cx9ps3 on 27.06.2023.
//

#include "AssetsIcon.hpp"
#include "AssetsWindow.hpp"
#include <misc/cpp/imgui_stdlib.h>
#include <core/assets/AssetsStorage.hpp>
#include <graphics/textures/ImageAsset.hpp>

using assets = hexen::engine::core::assets::AssetsHelper;

std::shared_ptr<hexen::engine::graphics::Texture2D> hexen::editor::gui::AssetIcon::fileIcon;
std::shared_ptr<hexen::engine::graphics::Texture2D> hexen::editor::gui::AssetIcon::animationFileIcon;
std::shared_ptr<hexen::engine::graphics::Texture2D> hexen::editor::gui::AssetIcon::entityFileIcon;
std::shared_ptr<hexen::engine::graphics::Texture2D> hexen::editor::gui::AssetIcon::folderIcon;
std::shared_ptr<hexen::engine::graphics::Texture2D> hexen::editor::gui::AssetIcon::sceneFileIcon;
std::shared_ptr<hexen::engine::graphics::Texture2D> hexen::editor::gui::AssetIcon::soundFileIcon;
std::shared_ptr<hexen::engine::graphics::Texture2D> hexen::editor::gui::AssetIcon::tilesetFileIcon;
hexen::editor::gui::AssetsWindow *hexen::editor::gui::AssetIcon::assetsWindow {nullptr};
hexen::engine::core::HashTable<hexen::engine::core::u32, std::string> hexen::editor::gui::AssetIcon::engineFileExtensions;

hexen::editor::gui::AssetIcon::AssetIcon(const std::filesystem::directory_entry &path, AssetsWindow *newAssetsWindow)
{
	HEXEN_ADD_TO_PROFILE()

	name = path.path().filename();
	pathToFile = path.path().string();
	fileName = name.string();

	assetsWindow = newAssetsWindow;

	if (fileIcon == nullptr)
	{
		//use static class members for memory optimization

		folderIcon = engine::graphics::Texture2D::create(assets::createAsset<engine::graphics::ImageAsset>("EditorIcons/FolderIcon.hasset", pathToFolderIcon) , engine::graphics::TextureFilter::LINEAR);
		soundFileIcon = engine::graphics::Texture2D::create(assets::createAsset<engine::graphics::ImageAsset>("EditorIcons/SoundIcon.hasset", pathToSoundFileIcon) , engine::graphics::TextureFilter::LINEAR);
		fileIcon = engine::graphics::Texture2D::create(assets::createAsset<engine::graphics::ImageAsset>("EditorIcons/FileIcon.hasset", pathToFileIcon) , engine::graphics::TextureFilter::LINEAR);
		sceneFileIcon = engine::graphics::Texture2D::create(assets::createAsset<engine::graphics::ImageAsset>("EditorIcons/SceneFileIcon.hasset", pathToSceneFileIcon) , engine::graphics::TextureFilter::LINEAR);
		animationFileIcon = engine::graphics::Texture2D::create(assets::createAsset<engine::graphics::ImageAsset>("EditorIcons/AnimationFileIcon.hasset", pathToAnimationFileIcon) , engine::graphics::TextureFilter::LINEAR);
		tilesetFileIcon = engine::graphics::Texture2D::create(assets::createAsset<engine::graphics::ImageAsset>("EditorIcons/TileFileIcon.hasset", pathToTilesetFileIcon) , engine::graphics::TextureFilter::LINEAR);
		entityFileIcon = engine::graphics::Texture2D::create(assets::createAsset<engine::graphics::ImageAsset>("EditorIcons/EntityFileIcon.hasset",pathToEntityFileIcon) , engine::graphics::TextureFilter::LINEAR);

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

			//imageFileIcon = engine::graphics::Texture2D::create(path.path().string() , engine::graphics::TextureFilter::LINEAR);
			//textureId = imageFileIcon->getId();
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
	HEXEN_ADD_TO_PROFILE()
	size = newSize;
}

void hexen::editor::gui::AssetIcon::draw()
{
	HEXEN_ADD_TO_PROFILE()
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
	HEXEN_ADD_TO_PROFILE()
	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload(PAYLOAD_NAME.c_str(), pathToFile.c_str(), (pathToFile.size() + 1) * sizeof(char));
		ImGui::EndDragDropSource();
	}
}

void hexen::editor::gui::AssetIcon::createDragAndDropTarget()
{
	HEXEN_ADD_TO_PROFILE()
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
	HEXEN_ADD_TO_PROFILE()
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

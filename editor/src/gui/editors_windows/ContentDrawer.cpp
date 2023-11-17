//
// Created by cx9ps3 on 19.06.2023.
//
#include "../../application/Application.hpp"
#include "../IconsFontAwesome5.hpp"
#include "ContentDrawer.hpp"
#include "MessageBox.hpp"
#include "Shortcuts.hpp"
#include "native_file_dialog/FileDialog.hpp"
#include <algorithm>
#include <core/assets/AssetsStorage.hpp>
#include <fstream>
#include <graphics/textures/ImageAsset.hpp>

using textures = hexen::engine::graphics::Texture2D;
using assets = hexen::engine::core::assets::AssetHelper;

hexen::editor::gui::ContentDrawer::ContentDrawer(std::string name) : GUIWindow(std::move(name))
{
	HEXEN_ADD_TO_PROFILE()
	setSize(glm::vec2(1280, 400));

	iconCallbacks = engine::core::memory::make_shared<AssetIconCallbacks>();
	deleteFileWindow = hexen::engine::core::memory::make_unique<DeleteFileWindow>("Delete");
	deleteSelectedFilesWindow = hexen::engine::core::memory::make_unique<DeleteSelectedFilesWindow>("Delete selected");
	copyingFilesWindow = hexen::engine::core::memory::make_unique<CopyingFilesWindow>("Copying");

	deleteSelectedFilesCallback = [this]()
	{
		deleteSelectedFilesWindow->setPaths(selectedFiles);
		deleteSelectedFilesWindow->setOpen(true);
		refresh();
	};

	refreshCallback = [this]()
	{
		refresh();
	};

	Shortcuts::addShortcut({ImGuiKey_LeftCtrl, ImGuiKey_R}, refreshCallback);
}

void hexen::editor::gui::ContentDrawer::begin()
{
	HEXEN_ADD_TO_PROFILE()
	deleteFileWindow->begin();
	deleteSelectedFilesWindow->begin();
	copyingFilesWindow->begin();
}

void hexen::editor::gui::ContentDrawer::draw()
{
	HEXEN_ADD_TO_PROFILE()
	ImGui::Begin(getName().c_str(), &isOpen, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_HorizontalScrollbar);

	if (Project::getCurrentProject() != nullptr)
	{
		if (!isRootDirectoryLoaded)
		{
			currentPath = Project::getCurrentProject()->getPath();
			isRootDirectoryLoaded = true;
			directoryList.emplace_back("/");
			refresh();
		}
		if (ImGui::BeginMenuBar())
		{
			for (hexen::engine::core::i32 i = 0; i < directoryList.size(); i++)
			{
				drawNode(i);
			}
			ImGui::EndMenuBar();
		}


		auto panelWitdh = ImGui::GetContentRegionAvail().x;
		auto cellSize = iconsSize.x + padding;
		auto columnNumber = static_cast<hexen::engine::core::i32>(panelWitdh / cellSize);

		ImGui::Columns(columnNumber, nullptr, false);
		showFilesInDirectory();
		ImGui::Columns(1);

		if (ImGui::SliderFloat("Icon Size", &iconsSize.x, 16, 256))
		{
			iconsSize.y = iconsSize.x;
			resizeIcons();
		};

		ImGui::SliderFloat("Padding", &padding, 0, 32);
		drawMenu();

		if (!ImGui::IsAnyItemHovered() && !isShowedContextMenu)
		{
			currentHoveredIcon = nullptr;
		}
	}


	deleteFileWindow->draw();
	deleteSelectedFilesWindow->draw();
	copyingFilesWindow->draw();

	getActionsFromDialogs();

	ImGui::End();
}

void hexen::editor::gui::ContentDrawer::end()
{
	HEXEN_ADD_TO_PROFILE()
	deleteFileWindow->end();
	deleteSelectedFilesWindow->end();
	copyingFilesWindow->end();
}

void hexen::editor::gui::ContentDrawer::drawNode(hexen::engine::core::i32 i)
{
	HEXEN_ADD_TO_PROFILE()
	auto nodeName = directoryList[i] + " " + ICON_FA_FOLDER;

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 50.0f);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 0.1f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 1.0f, 1.0f, 0.3f));

	ImGui::ArrowButton("arrow", ImGuiDir_Right);
	ImGui::SameLine(0, 0.0);
	if (ImGui::Button(nodeName.c_str()))
	{
		auto it = std::find(directoryList.begin(), directoryList.end(), directoryList[i]);
		if (it != directoryList.end())
		{
			directoryList.erase(it + 1, directoryList.end());
		}

		currentPath = Project::getCurrentProject()->getPath();
		for (const auto &directory : directoryList)
		{
			if (directory != "/")
			{
				currentPath = currentPath / directory;
			}
		}
		refresh();
	}
	ImGui::SameLine(0, 0.0);
	ImGui::PopStyleVar();
	ImGui::PopStyleColor(2);
}

void hexen::editor::gui::ContentDrawer::pushButtonStyle()
{
	HEXEN_ADD_TO_PROFILE()
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 1.0f, 1.0f, 0.1f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 1.0f, 1.0f, 0.1f));
}

void hexen::editor::gui::ContentDrawer::popButtonStyle()
{
	HEXEN_ADD_TO_PROFILE()
	ImGui::PopStyleColor(3);
}

void hexen::editor::gui::ContentDrawer::showFilesInDirectory()
{
	HEXEN_ADD_TO_PROFILE()
	pushButtonStyle();
	for (auto &icon : icons)
	{
		icon.draw();
	}
	popButtonStyle();
}


void hexen::editor::gui::ContentDrawer::refresh()
{
	HEXEN_ADD_TO_PROFILE()
	icons.clear();

	if (!currentPath.empty())
	{
		for (const auto &directoryIterator : std::filesystem::directory_iterator(currentPath))
		{
			auto directoryCallback = [this](const std::filesystem::path &path)
			{
				auto filename = path.filename().string();
				this->directoryList.push_back(filename);
				this->currentPath = this->currentPath / filename;
				this->refresh();
			};

			if (directoryIterator.is_directory())
			{
				engine::core::u32 textureID;
				textureID = getIconTextureID("directory_icon", "directory", pathToFolderIcon);
				icons.emplace_back(directoryIterator.path(), directoryCallback, this, textureID);
			}
			else
			{
				auto fileExtension = directoryIterator.path().extension().string();
				if (assetExtensions.isExtensionExist(fileExtension))
				{
					auto pathToIcon = assetExtensions.getPathToIcon(fileExtension);
					auto textureID = getIconTextureID(fileExtension, pathToIcon.filename(), pathToIcon);
					icons.emplace_back(directoryIterator.path(), iconCallbacks->getCallback(fileExtension), this, textureID);
				}
				else if (fileExtension == engine::graphics::ImageAsset::getExtension())
				{
					auto imageName = directoryIterator.path().filename();


					auto imageRootDirectory = directoryIterator.path().parent_path().filename();

					std::cout << "Image Name:" << imageName << "\n";
					std::cout << "Image Root Directory: " << imageRootDirectory << "\n";
					std::filesystem::path pathToImageAsset;

					if (imageRootDirectory.string() != Project::getCurrentProject()->getName())
					{
						pathToImageAsset = imageRootDirectory / imageName;
					}
					else
					{
						pathToImageAsset = imageName;
					}

					auto iconTexture = textures::create(assets::loadAsset<engine::graphics::ImageAsset>(pathToImageAsset), engine::graphics::TextureFilter::LINEAR);
					auto textureID = iconTexture->getId();
					iconsTexture[imageName.string()] = iconTexture;

					auto imageCallback = [this](const std::filesystem::path &path) {

					};

					icons.emplace_back(directoryIterator.path(), imageCallback, this, textureID);
				}
				else
				{
					auto fileCallback = [](const std::filesystem::path &path) {};
					engine::core::u32 textureID;
					textureID = getIconTextureID("file_icon", "FileIcon", pathToFileIcon);
					icons.emplace_back(directoryIterator.path(), fileCallback, this, textureID);
				}
			}
		}
	}
}

void hexen::editor::gui::ContentDrawer::resizeIcons()
{
	HEXEN_ADD_TO_PROFILE()
	for (auto &icon : icons)
	{
		icon.setSize(iconsSize);
	}
}

void hexen::editor::gui::ContentDrawer::drawMenu()
{
	HEXEN_ADD_TO_PROFILE()
	isShowedContextMenu = ImGui::BeginPopupContextWindow();
	if (isShowedContextMenu)
	{
		drawImportNewAssets();
		ImGui::Separator();
		drawCreateScene();
		drawCreateAnimation();
		drawCreateEntity();
		drawCreateTileset();
		ImGui::Separator();
		drawNewFolder();
		ImGui::Separator();
		drawRefresh();
		drawRename();
		drawDelete();
		ImGui::EndPopup();
	}
}

void hexen::editor::gui::ContentDrawer::drawImportNewAssets()
{
	HEXEN_ADD_TO_PROFILE()
	if (ImGui::MenuItem(ICON_FA_FILE_IMPORT " Import New Assets..."))
	{
		FileDialog fileDialog;
		INativeFileDialog::PathSet pathSet;
		INativeFileDialog::FileFilter fileFilter;
		fileFilter.push_back({{"All files"}, {"all"}});
		auto status = fileDialog.openDialog(fileFilter, "", &pathSet);
		if (status == INativeFileDialog::Status::STATUS_ERROR)
		{
			ImGuiMessageBox::add(std::string("Error"), std::string("Failed to import assets!"));
		}
		else if (status == INativeFileDialog::Status::STATUS_OK)
		{
			std::vector<std::filesystem::path> files;
			files.reserve(pathSet.count);

			for (const auto &path : pathSet.path)
			{
				files.emplace_back(path);
			}

			copyingFilesWindow->setCurrentPath(currentPath);
			copyingFilesWindow->setFilesToCopy(files);
			copyingFilesWindow->setOpen(true);
		}
	}
}

void hexen::editor::gui::ContentDrawer::drawDelete()
{
	HEXEN_ADD_TO_PROFILE()
	if (currentHoveredIcon != nullptr && selectedFiles.empty())
	{
		if (ImGui::MenuItem(ICON_FA_TRASH " Delete"))
		{
			deleteFileWindow->setPath(currentHoveredIcon->getPath());
			deleteFileWindow->setOpen(true);
			refresh();
		}
	}
	else if (!selectedFiles.empty())
	{
		if (ImGui::MenuItem(ICON_FA_DUMPSTER_FIRE " Delete selected files"))
		{
			deleteSelectedFilesCallback();
		}
	}
	else
	{
		ImGui::MenuItem(ICON_FA_TRASH " Delete", nullptr, false, false);
	}
}

void hexen::editor::gui::ContentDrawer::drawRename()
{
	HEXEN_ADD_TO_PROFILE()
	if (currentHoveredIcon != nullptr)
	{
		if (ImGui::MenuItem(ICON_FA_PENCIL_ALT " Rename"))
		{
			currentHoveredIcon->renameFile();
		}
	}
	else
	{
		ImGui::MenuItem(ICON_FA_PENCIL_ALT " Rename", nullptr, false, false);
	}
}

void hexen::editor::gui::ContentDrawer::getActionsFromDialogs()
{
	HEXEN_ADD_TO_PROFILE()
	dialogWindowActions.clear();
	dialogWindowActions.push_back(deleteFileWindow->getLastAction());
	dialogWindowActions.push_back(deleteSelectedFilesWindow->getLastAction());
	dialogWindowActions.push_back(copyingFilesWindow->getLastAction());

	auto it = std::find_if(dialogWindowActions.cbegin(), dialogWindowActions.cend(), [](auto action)
			{ return action == DialogWindow::Action::PRESSED_OK; });

	if (it != dialogWindowActions.cend())
	{
		refresh();
	}
}

void hexen::editor::gui::ContentDrawer::drawCreateEntity()
{
	HEXEN_ADD_TO_PROFILE()
	if (ImGui::MenuItem(ICON_FA_FILE_ALT " Create Entity..."))
	{
	}
}

void hexen::editor::gui::ContentDrawer::drawCreateTileset()
{
	HEXEN_ADD_TO_PROFILE()
	if (ImGui::MenuItem(ICON_FA_FILE_IMAGE " Create Tileset..."))
	{
	}
}

void hexen::editor::gui::ContentDrawer::drawCreateAnimation()
{
	HEXEN_ADD_TO_PROFILE()
	if (ImGui::MenuItem(ICON_FA_FILE_VIDEO " Create Animation..."))
	{
	}
}

void hexen::editor::gui::ContentDrawer::drawCreateScene()
{
	HEXEN_ADD_TO_PROFILE()
	if (ImGui::MenuItem(ICON_FA_MAP " Create Scene..."))
	{
	}
}

void hexen::editor::gui::ContentDrawer::drawRefresh()
{
	HEXEN_ADD_TO_PROFILE()
	if (ImGui::MenuItem("Refresh", "CTRL+R"))
	{
		refreshCallback();
	}
}

void hexen::editor::gui::ContentDrawer::drawNewFolder()
{
	HEXEN_ADD_TO_PROFILE()
	if (ImGui::MenuItem(ICON_FA_FOLDER " New Folder"))
	{
		std::filesystem::create_directory(currentPath / "New Folder");
		refresh();
	}
}

hexen::engine::core::u32 hexen::editor::gui::ContentDrawer::getIconTextureID(const std::string &extension, const std::filesystem::path &pathToAsset, const std::filesystem::path &pathToIcon)
{
	engine::core::u32 textureID {0};
	auto it = iconsTexture.find(extension);

	if (it == iconsTexture.end())
	{
		auto iconTexture = textures::create(assets::createAsset<engine::graphics::ImageAsset>(pathToAsset, pathToIcon, Application::getName()), engine::graphics::TextureFilter::LINEAR);
		iconsTexture[extension] = iconTexture;
		textureID = iconTexture->getId();
	}
	else
	{
		textureID = it->second->getId();
	}
	return textureID;
}

void hexen::editor::gui::ContentDrawer::addNewIcon(const std::string &extension, std::filesystem::path &pathToIcon, const std::function<void(const std::filesystem::path &)> &iconCallback)
{
	assetExtensions.addNewAssetExtension(extension, pathToIcon);
	iconCallbacks->addCallback(extension, iconCallback);
}

hexen::editor::gui::AssetExtensions::AssetExtensions()
{
	if (std::filesystem::exists(pathToFileWithExtensions))
	{
		std::ifstream file(pathToFileWithExtensions);
		assetExtensionsFile = nlohmann::json::parse(file);
		extensionsCount = assetExtensionsFile["extensions_array_count"];
		getAssetExtensions();
	}
}

hexen::editor::gui::FileExtensions hexen::editor::gui::AssetExtensions::getAssetExtensions()
{
	for (engine::core::u32 i = 0; i < extensionsCount; i++)
	{
		auto extension = assetExtensionsFile["extensions"][i]["file_extension"];
		fileExtensions[extension] = std::filesystem::path(assetExtensionsFile["extensions"][i]["path_to_icon"]);
	}
	return fileExtensions;
}

void hexen::editor::gui::AssetExtensions::addNewAssetExtension(const std::string &fileExtension, const std::filesystem::path &pathToIcon)
{
	assetExtensionsFile["extensions"][extensionsCount]["file_extension"] = fileExtension;
	assetExtensionsFile["extensions"][extensionsCount]["path_to_icon"] = pathToIcon;
	assetExtensionsFile["extensions_array_count"] = extensionsCount++;
}

bool hexen::editor::gui::AssetExtensions::isExtensionExist(const std::string &fileExtension)
{
	return fileExtensions.find(fileExtension) != fileExtensions.end();
}

std::filesystem::path hexen::editor::gui::AssetExtensions::getPathToIcon(const std::string &fileExtension)
{
	return fileExtensions[fileExtension];
}

hexen::editor::gui::AssetExtensions::~AssetExtensions()
{
	std::ofstream file(pathToFileWithExtensions);
	file << assetExtensionsFile;
}

//
// Created by cx9ps3 on 19.06.2023.
//
#include "AssetsWindow.hpp"
#include "../../project/Project.hpp"
#include "../IconsFontAwesome5.hpp"
#include "MessageBox.hpp"
#include "Shortcuts.hpp"
#include "core/graphics/texture/Texture.hpp"
#include "native_file_dialog/FileDialog.hpp"
#include <algorithm>
#include <iostream>


hexen::editor::gui::AssetsWindow::AssetsWindow(std::string name) : GUIWindow(std::move(name))
{
	setSize(glm::vec2(1280, 400));

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

void hexen::editor::gui::AssetsWindow::begin()
{
	deleteFileWindow->begin();
	deleteSelectedFilesWindow->begin();
	copyingFilesWindow->begin();
}

void hexen::editor::gui::AssetsWindow::draw()
{
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

void hexen::editor::gui::AssetsWindow::end()
{
	deleteFileWindow->end();
	deleteSelectedFilesWindow->end();
	copyingFilesWindow->end();
}

void hexen::editor::gui::AssetsWindow::drawNode(hexen::engine::core::i32 i)
{
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

void hexen::editor::gui::AssetsWindow::pushButtonStyle()
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 1.0f, 1.0f, 0.1f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 1.0f, 1.0f, 0.1f));
}

void hexen::editor::gui::AssetsWindow::popButtonStyle()
{
	ImGui::PopStyleColor(3);
}

void hexen::editor::gui::AssetsWindow::showFilesInDirectory()
{
	pushButtonStyle();
	for (auto &icon : icons)
	{
		icon.draw();
	}
	popButtonStyle();
}


void hexen::editor::gui::AssetsWindow::refresh()
{
	icons.clear();
	if (!currentPath.empty())
	{
		for (const auto &path : std::filesystem::directory_iterator(currentPath))
		{
			icons.emplace_back(path, this);
		}
	}
}

void hexen::editor::gui::AssetsWindow::resizeIcons()
{
	for (auto &icon : icons)
	{
		icon.setSize(iconsSize);
	}
}

void hexen::editor::gui::AssetsWindow::drawMenu()
{
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

void hexen::editor::gui::AssetsWindow::drawImportNewAssets()
{
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

void hexen::editor::gui::AssetsWindow::drawDelete()
{
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

void hexen::editor::gui::AssetsWindow::drawRename()
{

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

void hexen::editor::gui::AssetsWindow::getActionsFromDialogs()
{
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

void hexen::editor::gui::AssetsWindow::drawCreateEntity()
{
	if (ImGui::MenuItem(ICON_FA_FILE_ALT " Create Entity..."))
	{
	}
}

void hexen::editor::gui::AssetsWindow::drawCreateTileset()
{
	if (ImGui::MenuItem(ICON_FA_FILE_IMAGE " Create Tileset..."))
	{
	}
}

void hexen::editor::gui::AssetsWindow::drawCreateAnimation()
{
	if (ImGui::MenuItem(ICON_FA_FILE_VIDEO " Create Animation..."))
	{
	}
}

void hexen::editor::gui::AssetsWindow::drawCreateScene()
{
	if (ImGui::MenuItem(ICON_FA_MAP " Create Scene..."))
	{
	}
}

void hexen::editor::gui::AssetsWindow::drawRefresh()
{
	if (ImGui::MenuItem("Refresh", "CTRL+R"))
	{
		refreshCallback();
	}
}

void hexen::editor::gui::AssetsWindow::drawNewFolder()
{
	if (ImGui::MenuItem(ICON_FA_FOLDER " New Folder"))
	{
		std::filesystem::create_directory(currentPath / "New Folder");
		refresh();
	}
}

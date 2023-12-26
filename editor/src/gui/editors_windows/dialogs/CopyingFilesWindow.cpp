//
// Created by cx9ps3 on 26.06.2023.
//

#include "CopyingFilesWindow.hpp"
#include "../MessageBox.hpp"
#include <assets/AssetsStorage.hpp>
#include <graphics/textures/ImageAsset.hpp>
#include "../../../application/Application.hpp"
#include "../../../project/Project.hpp"

void hexen::editor::gui::CopyingFilesWindow::setFilesToCopy(const std::vector<std::filesystem::path> &files)
{
	HEXEN_ADD_TO_PROFILE();
	filesToCopy = files;
	copiedFiles = 0;
	currentFileToCopy = filesToCopy.cbegin();
}

void hexen::editor::gui::CopyingFilesWindow::setCurrentPath(const std::filesystem::path &currentPath)
{
	HEXEN_ADD_TO_PROFILE();
	this->currentPath = currentPath;
}

void hexen::editor::gui::CopyingFilesWindow::drawContent()
{
	HEXEN_ADD_TO_PROFILE();
	if (currentFileToCopy != filesToCopy.cend())
	{

		ImGui::Text(text.c_str(), currentFileToCopy->string().c_str());

		const ImU32 color = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
		const ImU32 background = ImGui::GetColorU32(ImGuiCol_Button);

		auto path = *currentFileToCopy;

		auto it = std::find(imagesExtensions.cbegin(), imagesExtensions.cend(), path.extension());
		if(it != imagesExtensions.cend())
		{
			engine::core::assets::AssetHelper::createAsset<engine::graphics::ImageAsset>(std::filesystem::relative(currentPath, Project::getCurrentProject()->getPath()) / path.filename(),path);
		}
		else
		{
			try
			{
				std::filesystem::copy(path, currentPath / path.filename(), std::filesystem::copy_options::overwrite_existing);
			}
			catch(const std::exception &exception)
			{
				std::cout << "ERROR: " << exception.what() << "\n";
			}
		}

		ImGui::ProgressBar(static_cast<float>(copiedFiles + 1) / static_cast<float>(filesToCopy.size()), ImVec2(0, 1));
		copiedFiles++;
		currentFileToCopy++;
	}
	else
	{
		setAction(Action::PRESSED_OK);
		ImGui::CloseCurrentPopup();
	}
	if (ImGui::Button("Cancel"))
	{
		setAction(Action::PRESSED_CANCEL);
		ImGui::CloseCurrentPopup();
	}
}

hexen::editor::gui::CopyingFilesWindow::CopyingFilesWindow(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace) : DialogWindow(std::move(name), parentDockspace)
{
	HEXEN_ADD_TO_PROFILE();
}

hexen::editor::gui::CopyingFilesWindow::CopyingFilesWindow(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace) : DialogWindow(name, parentDockspace)
{
	HEXEN_ADD_TO_PROFILE();
}

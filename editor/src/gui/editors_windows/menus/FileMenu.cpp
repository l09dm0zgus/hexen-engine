//
// Created by cx9ps3 on 19.06.2023.
//

#include "FileMenu.hpp"
#include "../../../project/Project.hpp"
#include "../../IconsFontAwesome5.hpp"
#include "../MessageBox.hpp"
#include "../Shortcuts.hpp"
#include "../native_file_dialog/FileDialog.hpp"
#include <imgui.h>

void hexen::editor::gui::FileMenu::begin()
{
	HEXEN_ADD_TO_PROFILE();
	newProjectWindow->begin();
}

void hexen::editor::gui::FileMenu::draw()
{
	HEXEN_ADD_TO_PROFILE();
	showMainMenu();
	newProjectWindow->draw();
}

void hexen::editor::gui::FileMenu::end()
{
	HEXEN_ADD_TO_PROFILE();
	newProjectWindow->end();
}

void hexen::editor::gui::FileMenu::showMainMenu()
{
	HEXEN_ADD_TO_PROFILE();
	if (ImGui::BeginMainMenuBar())
	{
		show();
		ImGui::EndMainMenuBar();
	}
}

void hexen::editor::gui::FileMenu::show()
{
	HEXEN_ADD_TO_PROFILE();
	auto callback = [this]()
	{
		showNewScene();
		showOpenScene();
		showOpenRecentScene();
		ImGui::Separator();
		showNewProject();
		showOpenProject();
		showSaveProject();
		ImGui::Separator();
		showSave();
		showSaveAs();
		ImGui::Separator();
		showExit();
	};
	showMenu(getName(), callback);
}

void hexen::editor::gui::FileMenu::showNewScene()
{
	HEXEN_ADD_TO_PROFILE();
	showMenuItem(ICON_FA_MAP " New Scene", "CTRL+N", newSceneCallback);
}

void hexen::editor::gui::FileMenu::showOpenScene()
{
	HEXEN_ADD_TO_PROFILE();
	showMenuItem(ICON_FA_FILE_IMPORT " Open Scene", "CTRL+O", openSceneCallback);
}

void hexen::editor::gui::FileMenu::showOpenRecentScene()
{
	HEXEN_ADD_TO_PROFILE();
	auto callback = [this]() {

	};
	showMenu(ICON_FA_FILE_IMPORT " Open Recent Scene", callback);
}

void hexen::editor::gui::FileMenu::showSave()
{
	HEXEN_ADD_TO_PROFILE();
	showMenuItem(ICON_FA_SAVE " Save", "CTRL+S", saveFileCallback);
}

void hexen::editor::gui::FileMenu::showSaveAs()
{
	HEXEN_ADD_TO_PROFILE();
	showMenuItem(ICON_FA_FOLDER_OPEN " Save As...", "CTRL+SHIFT+S", saveAsFileCallback);
}

void hexen::editor::gui::FileMenu::showNewProject()
{
	HEXEN_ADD_TO_PROFILE();
	auto callback = [this]()
	{
		newProjectWindow->setOpen(true);
	};
	showMenuItem(ICON_FA_FOLDER_OPEN " New Project...", "", callback);
}

void hexen::editor::gui::FileMenu::showOpenProject()
{
	HEXEN_ADD_TO_PROFILE();
	auto callback = [this]()
	{
		FileDialog fileDialog;
		INativeFileDialog::FileFilter filter;
		std::string const pathToProject;
		filter.push_back({{"Project"}, {"hxproj;"}});
		std::string path;

		auto status = fileDialog.openDialog(filter, pathToProject, path);

		if (status == INativeFileDialog::Status::STATUS_ERROR)
		{
			ImGuiMessageBox::add(std::string("Error!"), std::string("Failed to select project file!"));
		}
		else if (status == INativeFileDialog::Status::STATUS_OK)
		{
			Project::setCurrentProject(path);
		}
	};
	showMenuItem(ICON_FA_FILE " Open Project...", "", callback);
}

void hexen::editor::gui::FileMenu::showSaveProject()
{
	HEXEN_ADD_TO_PROFILE();
	auto callback = [this]()
	{
		if (Project::getCurrentProject() != nullptr)
		{
			Project::getCurrentProject()->save();
		}
	};
	showMenuItem(ICON_FA_SAVE " Save Project", "", callback);
}

void hexen::editor::gui::FileMenu::showExit()
{
	HEXEN_ADD_TO_PROFILE();
	auto callback = [this]()
	{
		exit(0);
	};
	showMenuItem(ICON_FA_WINDOW_CLOSE " Exit", "", callback);
}

void hexen::editor::gui::FileMenu::initialize()
{
	HEXEN_ADD_TO_PROFILE();
	saveAsFileCallback = []()
	{
		FileDialog fileDialog;
		INativeFileDialog::FileFilter filter;
		std::string const pathToProject;

		std::pair<std::string, std::string> allFiles;
		std::pair<std::string, std::string> sceneFile;

		allFiles.first = "All files";
		allFiles.second = "all";

		sceneFile.first = "Scene";
		sceneFile.second = "hxscene;";

		filter.push_back(allFiles);
		filter.push_back(sceneFile);

		std::string path;
		if (fileDialog.saveDialog(filter, pathToProject, path) == INativeFileDialog::Status::STATUS_ERROR)
		{
			ImGuiMessageBox::add(std::string("Error!"), std::string("Failed to saving file"));
		}
	};

	saveFileCallback = []() {

	};

	newSceneCallback = []() {

	};

	openSceneCallback = []()
	{
		FileDialog fileDialog;
		INativeFileDialog::FileFilter filter;
		std::string const pathToProject;
		filter.push_back({{"Scenes"}, {"hxscene;"}});
		std::string path;
		if (fileDialog.openDialog(filter, pathToProject, path) == INativeFileDialog::Status::STATUS_ERROR)
		{
			ImGuiMessageBox::add(std::string("Error!"), std::string("Failed to select scene file!"));
		}
	};


	Shortcuts::addShortcut({ImGuiKey_LeftCtrl, ImGuiKey_S}, saveFileCallback);
	Shortcuts::addShortcut({ImGuiKey_LeftCtrl, ImGuiKey_O}, openSceneCallback);
	Shortcuts::addShortcut({ImGuiKey_LeftCtrl, ImGuiKey_N}, newSceneCallback);
	Shortcuts::addShortcut({ImGuiKey_LeftCtrl, ImGuiKey_LeftShift, ImGuiKey_S}, saveAsFileCallback);
}

hexen::editor::gui::FileMenu::FileMenu(const std::string &name, const std::weak_ptr<Dockspace> &parentDockspace) : Menu(name, parentDockspace)
{
	HEXEN_ADD_TO_PROFILE();
	newProjectWindow = engine::core::memory::make_unique<NewProjectWindow>("New Project", parentDockspace);
	initialize();
}

hexen::editor::gui::FileMenu::FileMenu(std::string &&name, const std::weak_ptr<Dockspace> &parentDockspace) : Menu(std::move(name), parentDockspace)
{
	HEXEN_ADD_TO_PROFILE();
	newProjectWindow = engine::core::memory::make_unique<NewProjectWindow>("New Project", parentDockspace);
	initialize();
}

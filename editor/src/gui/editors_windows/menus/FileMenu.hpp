//
// Created by cx9ps3 on 19.06.2023.
//

#pragma once

#include "../dialogs/NewProjectWindow.hpp"
#include "Menu.hpp"

namespace hexen::editor::gui
{
	class FileMenu : public Menu
	{
	private:
		void showMainMenu();
		void showNewScene();
		void showOpenScene();
		void showOpenRecentScene();
		void showSave();
		void showSaveAs();
		void showNewProject();
		void showOpenProject();
		void showSaveProject();
		void show();
		void showExit();
		std::function<void()> saveFileCallback;
		std::function<void()> saveAsFileCallback;
		std::unique_ptr<NewProjectWindow> newProjectWindow;
		std::function<void()> newSceneCallback;
		std::function<void()> openSceneCallback;

	public:
		explicit FileMenu(std::string name);
		void begin() override;
		void draw() override;
		void end() override;
	};

}// namespace hexen::editor::gui

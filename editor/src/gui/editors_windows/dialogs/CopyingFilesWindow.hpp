//
// Created by cx9ps3 on 26.06.2023.
//
#pragma once

#include "DialogWindow.hpp"
#include <filesystem>

namespace hexen::editor::gui
{
	class CopyingFilesWindow : public DialogWindow
	{
	private:
		std::filesystem::path currentPath;
		std::vector<std::filesystem::path> filesToCopy;
		std::string text = "Copying file : %s";
		std::vector<std::filesystem::path>::const_iterator currentFileToCopy;
		engine::core::i32 copedFiles {0};
		void drawContent() override;

	public:
		explicit CopyingFilesWindow(std::string name);
		void setFilesToCopy(const std::vector<std::filesystem::path> &files);
		void setCurrentPath(const std::filesystem::path &currentPath);
	};
}// namespace hexen::editor::gui

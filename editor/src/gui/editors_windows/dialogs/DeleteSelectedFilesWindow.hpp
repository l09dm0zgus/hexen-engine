//
// Created by cx9ps3 on 26.06.2023.
//

#pragma once

#include "DeleteFileWindow.hpp"

namespace hexen::editor::gui
{
	class DeleteSelectedFilesWindow : public DeleteFileWindow
	{
	private:
		std::vector<std::filesystem::path> paths;
		void drawContent() override;

	public:
		explicit DeleteSelectedFilesWindow(std::string name);
		void setPaths(const std::vector<std::filesystem::path> &selectedFiles);
	};

}// namespace hexen::editor::gui

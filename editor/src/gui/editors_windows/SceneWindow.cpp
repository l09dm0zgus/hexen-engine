//
// Created by cx9ps3 on 09.06.2023.
//

#include "SceneWindow.hpp"


hexen::editor::gui::SceneWindow::SceneWindow(const std::string &name) : FramebufferWindow(name)
{
	HEXEN_ADD_TO_PROFILE()
}

void hexen::editor::gui::SceneWindow::renderFramebufferContent()
{
	HEXEN_ADD_TO_PROFILE()
	FramebufferWindow::renderFramebufferContent();
}

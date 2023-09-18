//
// Created by cx9ps3 on 15.06.2023.
//

#include "Shortcuts.hpp"
#include <core/Types.hpp>

std::map<hexen::editor::gui::Shortcuts::Keys, std::function<void()>> hexen::editor::gui::Shortcuts::shortcuts;

void hexen::editor::gui::Shortcuts::addShortcut(const Keys &keys, const std::function<void()> &callback)
{
	shortcuts[keys] = callback;
}

void hexen::editor::gui::Shortcuts::processInput()
{

	for (const auto &shortcut : shortcuts)
	{
		bool isPressed = true;
		for (auto key : shortcut.first)
		{
			isPressed = ImGui::IsKeyDown(key) && isPressed;
		}
		if (isPressed)
		{
			shortcut.second();
		}
	}
}

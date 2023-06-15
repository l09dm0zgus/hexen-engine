//
// Created by cx9ps3 on 15.06.2023.
//

#include <core/Types.h>
#include "Shortcuts.h"

std::map<edit::gui::Shortcuts::Keys ,std::function<void()>> edit::gui::Shortcuts::shortcuts;

void edit::gui::Shortcuts::addShortcut(const Keys &keys, const std::function<void()>& callback)
{
    shortcuts[keys] = callback;
}

void edit::gui::Shortcuts::processInput()
{

    for(const auto& shortcut : shortcuts)
    {
        bool isPressed = true;
        for (auto key : shortcut.first)
        {
            isPressed = ImGui::IsKeyDown(key) && isPressed;
        }
        if(isPressed)
        {
            shortcut.second();
        }
    }
}

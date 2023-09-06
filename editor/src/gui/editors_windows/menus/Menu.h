//
// Created by cx9ps3 on 19.06.2023.
//

#pragma once

#include <functional>
#include "../GUIWindow.h"

namespace hexen::editor::gui
{
    class Menu : public GUIWindow
    {
    public:
        explicit Menu(std::string name);
    protected:
        void showMenu(const std::string &name,const std::function<void()> &callback);
        void showMenuItem(const std::string &name, const std::string &shortcutText, const std::function<void()> &callback);
    };
}


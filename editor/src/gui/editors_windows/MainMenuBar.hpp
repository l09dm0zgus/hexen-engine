//
// Created by cx9ps3 on 10.06.2023.
//

#pragma once

#include "GUIWindow.hpp"
#include "menus/Menu.hpp"
#include "menus/FileMenu.hpp"

namespace hexen::editor::gui
{
    class MainMenuBar : public GUIWindow
    {
    private:
        std::vector<std::shared_ptr<Menu>> menus;
    public:
        explicit MainMenuBar(std::string name);
        void begin() override;
        void draw() override;
        void end() override;
    };

}



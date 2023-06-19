//
// Created by cx9ps3 on 10.06.2023.
//

#ifndef HEXENEDITOR_MAINMENUBAR_H
#define HEXENEDITOR_MAINMENUBAR_H
#include "GUIWindow.h"
#include "menus/Menu.h"
#include "menus/FileMenu.h"

namespace edit::gui
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


#endif //HEXENEDITOR_MAINMENUBAR_H

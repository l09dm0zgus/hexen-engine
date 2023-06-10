//
// Created by cx9ps3 on 10.06.2023.
//

#ifndef HEXENEDITOR_MAINMENUBAR_H
#define HEXENEDITOR_MAINMENUBAR_H

#include "GUIWindow.h"
#include <functional>

namespace edit::gui
{
    class MainMenuBar : public GUIWindow
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
        void showFileMenu();
        void showMenu(const std::string &name,const std::function<void()> &callback);
        void showMenuItem(const std::string &name,const std::string &hotkey,const std::function<void()> &callback);
    public:
        explicit MainMenuBar(std::string name);
        void begin() override;
        void draw() override;
        void end() override;
    };

}


#endif //HEXENEDITOR_MAINMENUBAR_H

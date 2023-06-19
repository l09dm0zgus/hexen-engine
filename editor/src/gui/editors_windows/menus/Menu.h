//
// Created by cx9ps3 on 19.06.2023.
//

#ifndef HEXENEDITOR_MENU_H
#define HEXENEDITOR_MENU_H

#include <functional>
#include "../GUIWindow.h"

namespace edit::gui
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



#endif //HEXENEDITOR_MENU_H

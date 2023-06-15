//
// Created by cx9ps3 on 15.06.2023.
//

#ifndef HEXENEDITOR_SHORTCUTS_H
#define HEXENEDITOR_SHORTCUTS_H
#include <map>
#include <functional>
#include <imgui.h>

namespace edit::gui
{
    class Shortcuts
    {
    public:
        using Keys = std::vector<ImGuiKey>;

        static void addShortcut(const Keys &keys, const std::function<void()>& callback);
        static void processInput();
    private:
        static std::map<Keys,std::function<void()>> shortcuts;
    };
}




#endif //HEXENEDITOR_SHORTCUTS_H

//
// Created by cx9ps3 on 19.06.2023.
//

#ifndef HEXENEDITOR_ASSETSWINDOW_H
#define HEXENEDITOR_ASSETSWINDOW_H
#include "GUIWindow.h"

namespace edit::gui
{
    class AssetsWindow : public GUIWindow
    {
    public:
        explicit AssetsWindow(std::string name);
        void begin() override;
        void draw() override;
        void end() override;
    };
}


#endif //HEXENEDITOR_ASSETSWINDOW_H

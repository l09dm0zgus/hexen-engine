//
// Created by cx9ps3 on 09.06.2023.
//

#ifndef HEXENEDITOR_GUIWINDOW_H
#define HEXENEDITOR_GUIWINDOW_H
#include <string>
#include <core/memory_pool/AllocatedObject.h>

namespace edit::gui
{
    class GUIWindow : public core::mem::AllocatedObject
    {
    public:
        std::string getName();
        virtual void draw() = 0;
        virtual void begin() = 0;
        virtual void end() = 0;
        virtual ~GUIWindow() = default;
        explicit GUIWindow(std::string name);
        GUIWindow(GUIWindow &&guiWindow) = delete;
        GUIWindow(const GUIWindow &guiWindow) = delete;
        GUIWindow& operator=(GUIWindow &&guiWindow) = delete;
        GUIWindow& operator=(const GUIWindow &guiWindow) = delete;
    private:
        std::string name;
    };
}

#endif //HEXENEDITOR_GUIWINDOW_H

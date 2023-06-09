//
// Created by cx9ps3 on 09.06.2023.
//

#ifndef HEXENEDITOR_DOCKSPACE_H
#define HEXENEDITOR_DOCKSPACE_H
#include <core/Types.h>
#include "editors_windows/GUIWindow.h"
namespace edit::gui
{
    class Dockspace
    {
    public:
        enum class DockingPosition : core::u8
        {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
        void draw();
        void begin();
        void end();
        void attachWindow(std::shared_ptr<GUIWindow> guiWindow,const DockingPosition &dockingPosition);
    private:
        bool isAttachedWindow{true};
        void setWindowsInDockspace();
        core::u32 id;
        core::u32 dockUpId{0};
        core::u32 dockDownId{0};
        core::u32 dockLeftId{0};
        core::u32 dockRightId{0};
        std::vector<std::shared_ptr<GUIWindow>> windows;
        core::HashTable<std::string,DockingPosition> dockingPositions;
    };
}



#endif //HEXENEDITOR_DOCKSPACE_H

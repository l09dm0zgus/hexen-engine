//
// Created by cx9ps3 on 26.06.2023.
//

#ifndef HEXENEDITOR_COPYINGFILESSTATUS_H
#define HEXENEDITOR_COPYINGFILESSTATUS_H
#include "GUIWindow.h"

namespace edit::gui
{
    class CopyingFilesStatus : public  GUIWindow
    {
    private:
        bool isOpen = false;
        std::string currentFile;
        std::string text = "Copying file : %s";
    public:
        explicit CopyingFilesStatus(std::string name);
        void setCurrentFile(const std::string &pathToFile);
        void setOpen(bool newIsOpen);
        void begin() override;
        void end() override;
        void draw() override;
    };
}

#endif //HEXENEDITOR_COPYINGFILESSTATUS_H

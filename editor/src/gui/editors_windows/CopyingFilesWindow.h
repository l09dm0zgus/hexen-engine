//
// Created by cx9ps3 on 26.06.2023.
//

#ifndef HEXENEDITOR_COPYINGFILESWINDOW_H
#define HEXENEDITOR_COPYINGFILESWINDOW_H
#include "GUIWindow.h"
#include <filesystem>

namespace edit::gui
{
    class CopyingFilesWindow : public  GUIWindow
    {
    private:
        bool isOpen = false;
        std::filesystem::path currentPath;
        std::vector<std::filesystem::path> filesToCopy;
        std::string text = "Copying file : %s";
        std::vector<std::filesystem::path>::const_iterator currentFileToCopy;
    public:
        explicit CopyingFilesWindow(std::string name);
        void setFilesToCopy(const std::vector<std::filesystem::path> &files);
        void setCurrentPath(const std::filesystem::path &currentPath);
        void setOpen(bool newIsOpen);
        void begin() override;
        void end() override;
        void draw() override;
    };
}

#endif //HEXENEDITOR_COPYINGFILESWINDOW_H

//
// Created by cx9ps3 on 26.06.2023.
//

#ifndef HEXENEDITOR_DELETEFILEWINDOW_H
#define HEXENEDITOR_DELETEFILEWINDOW_H
#include "GUIWindow.h"
#include <filesystem>
namespace edit::gui
{
    class DeleteFileWindow : public GUIWindow
    {
    private:
        bool isOpen = false;
        void drawPopUp();
        std::string path;
    protected:
        std::function<void()> deleteCallback;
        std::string text = "Delete file :%s ?";
    public:
        explicit DeleteFileWindow(std::string name);
        void setPath(const std::string &pathToFile);
        void setOpen(bool newIsOpen);
        void begin() override;
        void end() override;
        void draw() override;

    };
}

#endif //HEXENEDITOR_DELETEFILEWINDOW_H

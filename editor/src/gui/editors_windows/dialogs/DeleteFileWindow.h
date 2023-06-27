//
// Created by cx9ps3 on 26.06.2023.
//

#ifndef HEXENEDITOR_DELETEFILEWINDOW_H
#define HEXENEDITOR_DELETEFILEWINDOW_H
#include "DialogWindow.h"
#include <filesystem>
namespace edit::gui
{
    class DeleteFileWindow : public DialogWindow
    {
    private:
        void drawPopUp();
        std::string path;
    protected:
        std::function<void()> deleteCallback;
        std::string text = "Delete file :%s ?";
        void drawContent() override;
    public:
        explicit DeleteFileWindow(std::string name);
        void setPath(const std::string &pathToFile);
    };
}

#endif //HEXENEDITOR_DELETEFILEWINDOW_H

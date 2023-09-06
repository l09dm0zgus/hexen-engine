//
// Created by cx9ps3 on 26.06.2023.
//

#pragma once

#include "DialogWindow.h"
#include <filesystem>
namespace hexen::editor::gui
{
    class DeleteFileWindow : public DialogWindow
    {
    private:
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


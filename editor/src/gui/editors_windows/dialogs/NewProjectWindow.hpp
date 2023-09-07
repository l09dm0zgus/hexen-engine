//
// Created by cx9ps3 on 16.06.2023.
//

#pragma once

#include <core/Types.hpp>
#include "DialogWindow.hpp"

namespace hexen::editor::gui
{
    class NewProjectWindow : public DialogWindow
    {
    private:
        enum ArraySizes : engine::core::u64
        {
            PROJECT_NAME_SIZE = 256,
            PATH_TO_PROJECT_SIZE = 512,
        };
        char projectName[ArraySizes::PROJECT_NAME_SIZE]{'0'};
        char pathToProject[PATH_TO_PROJECT_SIZE]{'0'};
        std::string projectPath;
        void clearStrings();
        void drawContent() override;
    public:
        std::string getProjectPath();
        explicit NewProjectWindow(std::string name);
    };
}




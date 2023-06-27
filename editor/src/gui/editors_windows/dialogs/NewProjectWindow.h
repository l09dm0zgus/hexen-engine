//
// Created by cx9ps3 on 16.06.2023.
//

#ifndef HEXENEDITOR_NEWPROJECTWINDOW_H
#define HEXENEDITOR_NEWPROJECTWINDOW_H
#include <core/Types.h>
#include "DialogWindow.h"

namespace edit::gui
{
    class NewProjectWindow : public DialogWindow
    {
    private:
        enum ArraySizes : core::u64
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



#endif //HEXENEDITOR_NEWPROJECTWINDOW_H

//
// Created by cx9ps3 on 26.06.2023.
//

#ifndef HEXENEDITOR_DELETESELECTEDFILESWINDOW_H
#define HEXENEDITOR_DELETESELECTEDFILESWINDOW_H
#include "DeleteFileWindow.h"

namespace edit::gui
{
    class DeleteSelectedFilesWindow : public DeleteFileWindow
    {
    private:
        std::vector<std::filesystem::path> paths;
        void drawContent() override;
    public:
        explicit DeleteSelectedFilesWindow(std::string name);
        void setPaths(const std::vector<std::filesystem::path> &selectedFiles);
    };

}


#endif //HEXENEDITOR_DELETESELECTEDFILESWINDOW_H

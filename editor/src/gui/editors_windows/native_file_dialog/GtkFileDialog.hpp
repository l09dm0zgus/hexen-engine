//
// Created by cx9ps3 on 12.06.2023.
//

#pragma once

#include "INativeFileDialog.hpp"

#include <gtk/gtk.h>

namespace hexen::editor::gui
{
    class GTKFileDialog  : public INativeFileDialog
    {
    public:
        Status openDialog(const FileFilter &filterList,const std::string &defaultPath,std::string &pathToFile) override;
        Status openDialog(const FileFilter &filterList,const std::string &defaultPath, PathSet *pathToFiles) override;
        Status saveDialog(const FileFilter &filterList,const std::string &defaultPath,std::string &pathToFile) override;
        Status pickDialog(const std::string &defaultPath,std::string &pathToFile) override;

    private:
        void addFiltersToDialog(GtkWidget *dialog,const FileFilter &fileFilter);
        void setDefaultPath(GtkWidget *dialog,const std::string &defaultPath);
        Status allocatePathSet(GSList *fileList, PathSet *pathSet);
        void waitForCleanUp();
    };
}

//
// Created by cx9ps3 on 14.06.2023.
//

#include "FileDialog.h"

#if defined(IS_UNIX)
#include "GtkFileDialog.h"
#elif defined(IS_WINDOWS)
#include "WindowsFileDialog.h"
#endif

edit::gui::FileDialog::FileDialog()
{
#if defined(IS_UNIX)
    nativeFileDialog = core::mem::make_unique<GTKFileDialog>();
#elif defined(IS_WINDOWS)
    nativeFileDialog = core::mem::make_unique<WindowsFileDialog>();
#endif

}

edit::gui::INativeFileDialog::Status edit::gui::FileDialog::openDialog(const edit::gui::INativeFileDialog::FileFilter &filterList,const std::string &defaultPath, std::string &pathToFile)
{
    return nativeFileDialog->openDialog(filterList,defaultPath,pathToFile);
}

edit::gui::INativeFileDialog::Status edit::gui::FileDialog::openDialog(const edit::gui::INativeFileDialog::FileFilter &filterList,const std::string &defaultPath, edit::gui::INativeFileDialog::PathSet *pathToFiles)
{
    return nativeFileDialog->openDialog(filterList,defaultPath,pathToFiles);;
}

edit::gui::INativeFileDialog::Status edit::gui::FileDialog::saveDialog(const edit::gui::INativeFileDialog::FileFilter &filterList,const std::string &defaultPath, std::string &pathToFile)
{
    return nativeFileDialog->saveDialog(filterList,defaultPath,pathToFile);;
}

edit::gui::INativeFileDialog::Status edit::gui::FileDialog::pickDialog(const std::string &defaultPath, std::string &pathToFile)
{
    return nativeFileDialog->pickDialog(defaultPath,pathToFile);;
}

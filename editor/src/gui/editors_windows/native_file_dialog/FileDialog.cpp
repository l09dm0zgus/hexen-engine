//
// Created by cx9ps3 on 14.06.2023.
//

#include "FileDialog.hpp"

#if defined(__unix__)
#include "GtkFileDialog.h"
#elif defined(WIN32)
#include "WindowsFileDialog.hpp"
#endif

hexen::editor::gui::FileDialog::FileDialog()
{
#if defined(__unix__ )
    nativeFileDialog = core::mem::make_unique<GTKFileDialog>();
#elif defined(WIN32)
    nativeFileDialog = engine::core::memory::make_unique<WindowsFileDialog>();
#endif

}

hexen::editor::gui::INativeFileDialog::Status hexen::editor::gui::FileDialog::openDialog(const hexen::editor::gui::INativeFileDialog::FileFilter &filterList,const std::string &defaultPath, std::string &pathToFile)
{
    return nativeFileDialog->openDialog(filterList,defaultPath,pathToFile);
}

hexen::editor::gui::INativeFileDialog::Status hexen::editor::gui::FileDialog::openDialog(const hexen::editor::gui::INativeFileDialog::FileFilter &filterList,const std::string &defaultPath, hexen::editor::gui::INativeFileDialog::PathSet *pathToFiles)
{
    return nativeFileDialog->openDialog(filterList,defaultPath,pathToFiles);;
}

hexen::editor::gui::INativeFileDialog::Status hexen::editor::gui::FileDialog::saveDialog(const hexen::editor::gui::INativeFileDialog::FileFilter &filterList,const std::string &defaultPath, std::string &pathToFile)
{
    return nativeFileDialog->saveDialog(filterList,defaultPath,pathToFile);;
}

hexen::editor::gui::INativeFileDialog::Status hexen::editor::gui::FileDialog::pickDialog(const std::string &defaultPath, std::string &pathToFile)
{
    return nativeFileDialog->pickDialog(defaultPath,pathToFile);;
}

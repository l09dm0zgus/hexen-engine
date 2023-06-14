//
// Created by cx9ps3 on 24.05.2023.
//
#include <iostream>
#include "application/Application.h"
#include <filesystem>
#include "../../../RealOne-Engine/editor/src/gui/file_dialog/FileDialog.h"

int main()
{
    //edit::Application app;
  //  app.run();
  edit::gui::FileDialog fileDialog;
  edit::gui::INativeFileDialog::PathSet pathSet;
  edit::gui::INativeFileDialog::FileFilter fileFilter;
  fileFilter.push_back({{"Executable"},{"dll;exe;"}});
  fileDialog.openDialog(fileFilter,"",&pathSet);
  for(const auto & path : pathSet.path)
  {
      std::cout << path << std::endl;
  }
}
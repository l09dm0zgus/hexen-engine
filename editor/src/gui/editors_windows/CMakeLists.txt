cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})

target_sources(${EDITOR_NAME} PRIVATE
        SceneWindow.h
        SceneWindow.cpp
        GUIWindow.cpp
        GUIWindow.h
        MainMenuBar.h
        MainMenuBar.cpp
        Shortcuts.h
        Shortcuts.cpp
        dialogs/NewProjectWindow.h
        dialogs/NewProjectWindow.cpp
        MessageBox.h
        MessageBox.cpp
        AssetsWindow.h
        AssetsWindow.cpp
        AssetsIcon.h
        AssetsIcon.cpp
        )

add_subdirectory(native_file_dialog)
add_subdirectory(menus)
add_subdirectory(dialogs)
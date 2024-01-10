cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})

target_sources(${EDITOR_NAME} PRIVATE
        SceneWindow.hpp
        SceneWindow.cpp
        GUIWindow.cpp
        GUIWindow.hpp
        MainMenuBar.hpp
        MainMenuBar.cpp
        Shortcuts.hpp
        Shortcuts.cpp
        dialogs/NewProjectWindow.hpp
        dialogs/NewProjectWindow.cpp
        MessageBox.hpp
        MessageBox.cpp
        ContentDrawer.hpp
        ContentDrawer.cpp
        AssetsIcon.hpp
        AssetsIcon.cpp
        SceneHierarchyWindow.hpp
        SceneHierarchyWindow.cpp
        FramebufferWindow.hpp
        FramebufferWindow.cpp
        TilesetEditor.hpp
        TilesetEditor.cpp
        )

add_subdirectory(native_file_dialog)
add_subdirectory(menus)
add_subdirectory(dialogs)
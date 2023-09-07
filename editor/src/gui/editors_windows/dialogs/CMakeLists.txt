cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})

target_sources(${EDITOR_NAME} PRIVATE
        DialogWindow.hpp
        DialogWindow.cpp
        DeleteFileWindow.hpp
        DeleteFileWindow.cpp
        DeleteSelectedFilesWindow.hpp
        DeleteSelectedFilesWindow.cpp
        CopyingFilesWindow.hpp
        CopyingFilesWindow.cpp
        )
cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})

target_sources(${EDITOR_NAME} PRIVATE
        DialogWindow.h
        DialogWindow.cpp
        DeleteFileWindow.h
        DeleteFileWindow.cpp
        DeleteSelectedFilesWindow.h
        DeleteSelectedFilesWindow.cpp
        CopyingFilesWindow.h
        CopyingFilesWindow.cpp
        )
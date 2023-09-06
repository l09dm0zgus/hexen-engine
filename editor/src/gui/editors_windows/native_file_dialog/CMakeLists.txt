cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")

    target_sources(${EDITOR_NAME} PRIVATE
            WindowsFileDialog.h
            WindowsFileDialog.cpp
    )
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_sources(${EDITOR_NAME} PRIVATE
            GtkFileDialog.h
            GtkFileDialog.cpp
    )
endif ()

target_sources(${EDITOR_NAME} PRIVATE
      FileDialog.h
      FileDialog.cpp
      INativeFileDialog.h
        )
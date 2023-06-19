cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})
target_sources(${EDITOR_NAME} PRIVATE
        EditorGUI.cpp
        EditorGUI.h
        Style.h
        Style.cpp
        Dockspace.h
        Dockspace.cpp
        IconsFontAwesome5.h
        )

add_subdirectory(editors_windows)
cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})
target_sources(${EDITOR_NAME} PRIVATE
        EditorGUI.cpp
        EditorGUI.hpp
        Style.hpp
        Style.cpp
        Dockspace.hpp
        Dockspace.cpp
        IconsFontAwesome5.hpp
        )

add_subdirectory(editors_windows)
cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})
target_sources(${EDITOR_NAME} PRIVATE
        debug_rendering/DrawGridCommand.hpp
        debug_rendering/DrawGridCommand.cpp
        debug_rendering/DebugGridComponent.hpp
        debug_rendering/DebugGridComponent.cpp
        EditorCameraComponent.hpp
        EditorCameraComponent.cpp
        )

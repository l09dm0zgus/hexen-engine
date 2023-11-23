cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})
target_sources(${EDITOR_NAME} PRIVATE
        debug_rendering/DrawGridCommand.hpp
        debug_rendering/DrawGridCommand.cpp
        debug_rendering/GridComponent.hpp
        debug_rendering/GridComponent.cpp
        debug_rendering/DrawCheckerboardQuad.hpp
        debug_rendering/DrawCheckerboardQuad.cpp
        debug_rendering/CheckerboardQuadComponent.hpp
        debug_rendering/CheckerboardQuadComponent.cpp
        EditorCameraComponent.hpp
        EditorCameraComponent.cpp
        )

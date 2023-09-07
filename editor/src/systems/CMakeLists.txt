cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})
target_sources(${EDITOR_NAME} PRIVATE
        DebugRenderSystem.hpp
        DebugRenderSystem.cpp
        EditorSystemsManager.hpp
        EditorSystemsManager.cpp
        )

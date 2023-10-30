cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})
target_sources(${EDITOR_NAME} PRIVATE
        EditorRenderSystem.hpp
        EditorRenderSystem.cpp
        EditorSystemsManager.hpp
        EditorSystemsManager.cpp
        )

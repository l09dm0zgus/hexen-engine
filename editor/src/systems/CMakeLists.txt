cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})
target_sources(${EDITOR_NAME} PRIVATE
        DebugRenderSystem.h
        DebugRenderSystem.cpp
        EditorSystemsManager.h
        EditorSystemsManager.cpp
        )

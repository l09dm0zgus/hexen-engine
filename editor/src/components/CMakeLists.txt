cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})
target_sources(${EDITOR_NAME} PRIVATE
        debug_rendering/DebugGridComponent.h
        debug_rendering/DebugGridComponent.cpp
        )

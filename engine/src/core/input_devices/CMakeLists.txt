cmake_minimum_required(VERSION 3.6)
target_sources(${ENGINE_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Mouse.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Mouse.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gamepad.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gamepad.cpp
)
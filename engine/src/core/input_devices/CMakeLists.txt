cmake_minimum_required(VERSION 3.20)
project(Hexen)

message(STATUS "Engine Name:" ${ENGINE_NAME})
target_sources(${ENGINE_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Mouse.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Mouse.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gamepad.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gamepad.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Keyboard.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Keyboard.cpp
)
cmake_minimum_required(VERSION 3.20)
project(Hexen)


target_sources(${CORE_MODULE_NAME} PRIVATE
        Mouse.hpp
        Mouse.cpp
        Gamepad.hpp
        Gamepad.cpp
        Keyboard.hpp
        Keyboard.cpp
)
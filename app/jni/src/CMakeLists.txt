cmake_minimum_required(VERSION 3.6)

project(${PROJECT_NAME})


find_library(SDL2_image SDL2_image)
find_library(SDL2 SDL2)
find_library(OpenGL OpenGL)

add_library(main SHARED)

target_sources(main PRIVATE main.cpp
        core/window/Window.cpp
        core/window/Window.h
        core/application/Application.h
        core/application/Application.cpp)

target_link_libraries(main SDL2 SDL2_image GLESv2)


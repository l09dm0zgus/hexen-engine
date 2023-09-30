cmake_minimum_required(VERSION 3.20)
project(Hexen)

message(STATUS "Engine Name:" ${ENGINE_NAME})

target_sources(${ENGINE_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/IGUI.hpp)
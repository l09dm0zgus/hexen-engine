cmake_minimum_required(VERSION 3.6)
project(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Mouse.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Mouse.cpp
)
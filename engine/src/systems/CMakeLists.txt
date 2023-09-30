cmake_minimum_required(VERSION 3.20)
project(Hexen)

message(STATUS "Engine Name:" ${ENGINE_NAME})

target_sources(${ENGINE_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderSystem.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderSystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IGamePlaySystem.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IRenderSystem.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TaskSystem.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TaskSystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SystemsManager.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SystemsManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/InputSystem.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/InputSystem.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/InputHelper.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/InputHelper.cpp
        )
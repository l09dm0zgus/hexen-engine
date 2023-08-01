cmake_minimum_required(VERSION 3.6)
project(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderSystem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderSystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IGamePlaySystem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/IRenderSystem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TaskSystem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TaskSystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SystemsManager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/SystemsManager.cpp
        )
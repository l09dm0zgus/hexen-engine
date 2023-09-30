cmake_minimum_required(VERSION 3.20)
project(Hexen)

message(STATUS "Engine Name:" ${ENGINE_NAME})

target_sources(${ENGINE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/scene/SceneEntity.h
        ${CMAKE_CURRENT_SOURCE_DIR}/scene/SceneEntity.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Entity.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Entity.cpp
        )
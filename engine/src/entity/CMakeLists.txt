cmake_minimum_required(VERSION 3.6)
project(${PROJECT_NAME})


target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/scene/SceneEntity.h
        ${CMAKE_CURRENT_SOURCE_DIR}/scene/SceneEntity.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Entity.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Entity.cpp
        )
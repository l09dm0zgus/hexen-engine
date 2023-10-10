cmake_minimum_required(VERSION 3.20)
project(Hexen)

if(NOT TARGET ${ENTITY_MODULE_NAME} )
        add_library(${ENTITY_MODULE_NAME} SHARED)
endif(NOT TARGET ${ENTITY_MODULE_NAME})

target_sources(${ENTITY_MODULE_NAME} PRIVATE
        scene/Scene.hpp
        scene/Scene.cpp
        scene/SceneManager.hpp
        scene/SceneManager.cpp
        scene/Grid.hpp
        scene/Grid.cpp
        scene/SceneEntity.h
        scene/SceneEntity.cpp
        Entity.h
        Entity.cpp
        )

target_include_directories(${ENTITY_MODULE_NAME} PRIVATE ${CORE_ENGINE_INCLUDE_DIR})
target_include_directories(${ENTITY_MODULE_NAME} PRIVATE ${COMPONENTS_ENGINE_INCLUDE_DIR})
target_link_libraries(${ENTITY_MODULE_NAME} PRIVATE ${CORE_MODULE_NAME} ${COMPONENTS_MODULE_NAME} ${SYSTEMS_MODULE_NAME})

if(MSVC)
        target_compile_options(${ENTITY_MODULE_NAME} PRIVATE /W4)
else()
        target_compile_options(${ENTITY_MODULE_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
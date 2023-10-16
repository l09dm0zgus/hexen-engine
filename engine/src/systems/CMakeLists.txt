cmake_minimum_required(VERSION 3.20)
project(Hexen)

if (NOT TARGET ${SYSTEMS_MODULE_NAME})
        add_library(${SYSTEMS_MODULE_NAME} SHARED)
endif (NOT TARGET ${SYSTEMS_MODULE_NAME})

target_sources(${SYSTEMS_MODULE_NAME} PRIVATE
        RenderSystem.hpp
        RenderSystem.cpp
        IGamePlaySystem.hpp
        IRenderSystem.hpp
        TaskSystem.hpp
        TaskSystem.cpp
        SystemsManager.hpp
        SystemsManager.cpp
        InputSystem.hpp
        InputSystem.cpp
        InputHelper.hpp
        InputHelper.cpp
        GameLoop.hpp
        GameLoop.cpp
        )

target_include_directories(${SYSTEMS_MODULE_NAME} PRIVATE ${CORE_ENGINE_INCLUDE_DIR})
target_include_directories(${SYSTEMS_MODULE_NAME} PRIVATE ${COMPONENTS_ENGINE_INCLUDE_DIR})
target_link_libraries(${SYSTEMS_MODULE_NAME} PRIVATE ${CORE_MODULE_NAME} ${COMPONENTS_MODULE_NAME})
target_include_directories(${SYSTEMS_MODULE_NAME} PUBLIC ${PHMAP_INCLUDE_DIR})

if(MSVC)
        target_compile_options(${SYSTEMS_MODULE_NAME} PRIVATE /W4)
else()
        target_compile_options(${SYSTEMS_MODULE_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
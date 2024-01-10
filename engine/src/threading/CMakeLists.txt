cmake_minimum_required(VERSION 3.20)
project(Hexen)

if (NOT TARGET ${THREADING_MODULE_NAME})
    add_library(${THREADING_MODULE_NAME} STATIC)
endif (NOT TARGET ${THREADING_MODULE_NAME})

target_sources(${THREADING_MODULE_NAME} PRIVATE
        TaskSystem.hpp
        TaskSystem.cpp
)

target_include_directories(${THREADING_MODULE_NAME} PUBLIC ${CORE_ENGINE_INCLUDE_DIR})
target_include_directories(${THREADING_MODULE_NAME} PUBLIC ${CONTEXT_INCLUDE_DIR})
target_include_directories(${THREADING_MODULE_NAME} PUBLIC ${JSON_INCLUDE_DIR})

if(MSVC)
    target_compile_options(${THREADING_MODULE_NAME} PRIVATE /W4)
else()
    target_compile_options(${THREADING_MODULE_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
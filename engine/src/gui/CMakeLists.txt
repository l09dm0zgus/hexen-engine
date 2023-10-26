cmake_minimum_required(VERSION 3.20)
project(Hexen)
if (NOT TARGET ${GUI_MODULE_NAME})
    add_library(${GUI_MODULE_NAME} STATIC)
endif (NOT TARGET ${GUI_MODULE_NAME})

target_sources(${GUI_MODULE_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/IGUI.hpp)

target_include_directories(${GUI_MODULE_NAME} PRIVATE ${CORE_ENGINE_INCLUDE_DIR})
target_link_libraries(${GUI_MODULE_NAME} PUBLIC ${CORE_MODULE_NAME})

if(MSVC)
    target_compile_options(${GUI_MODULE_NAME} PRIVATE /W4)
else()
    target_compile_options(${GUI_MODULE_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
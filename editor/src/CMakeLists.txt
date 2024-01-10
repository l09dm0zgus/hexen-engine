cmake_minimum_required(VERSION 3.20)
set(EDITOR_NAME HexenEditor CACHE INTERNAL "")
project(${EDITOR_NAME})

add_executable(${EDITOR_NAME})

add_subdirectory(gui)
add_subdirectory(systems)
add_subdirectory(components)

target_sources(${EDITOR_NAME} PRIVATE
        Application.rc
        main.cpp
        application/Application.cpp
        application/Application.hpp
        application/EditorGameLoop.hpp
        application/EditorGameLoop.cpp
        project/Project.hpp
        project/Project.cpp
        )

if(MSVC)
        target_compile_options(${EDITOR_NAME} PRIVATE /W4)
else()
        target_compile_options(${EDITOR_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        target_link_libraries(${EDITOR_NAME}  PRIVATE ${CORE_MODULE_NAME} ${RENDER_MODULE_NAME} ${COMPONENTS_MODULE_NAME} ${SYSTEMS_MODULE_NAME} ${ENTITY_MODULE_NAME} ${GUI_MODULE_NAME} ${THREADING_MODULE_NAME})
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        find_package(PkgConfig REQUIRED)
        pkg_check_modules (GTK2 REQUIRED gtk+-2.0)
        target_include_directories(${EDITOR_NAME} PRIVATE  ${GTK2_INCLUDE_DIRS})
        target_link_libraries(${EDITOR_NAME} PRIVATE ${GTK2_LIBRARIES} ${CORE_MODULE_NAME} ${RENDER_MODULE_NAME} ${COMPONENTS_MODULE_NAME} ${SYSTEMS_MODULE_NAME} ${ENTITY_MODULE_NAME} ${GUI_MODULE_NAME} ${THREADING_MODULE_NAME})
endif ()

target_include_directories(${EDITOR_NAME} PRIVATE ${BOOST_CONTEXT_INCLUDE_DIR})
target_include_directories(${EDITOR_NAME} PRIVATE ${IMGUI_INCLUDE_DIR})
target_include_directories(${EDITOR_NAME} PRIVATE ${PARENT_DIR}/engine/src)



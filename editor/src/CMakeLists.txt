cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})

add_executable(${EDITOR_NAME})

add_subdirectory(gui)
add_subdirectory(systems)
add_subdirectory(components)

target_sources(${EDITOR_NAME} PRIVATE
        Application.rc
        main.cpp
        application/Application.cpp
        application/Application.h
        application/EditorGameLoop.h
        application/EditorGameLoop.cpp
        project/Project.h
        project/Project.cpp
        )



target_include_directories(${EDITOR_NAME} PRIVATE ${IMGUI_INCLUDE_DIR})
target_include_directories(${EDITOR_NAME} PRIVATE ${PARENT_DIR}/engine/src)




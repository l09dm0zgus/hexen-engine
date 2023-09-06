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


if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        target_link_libraries(${EDITOR_NAME} nlohmann_json::nlohmann_json SDL3_image::SDL3_image SDL3::SDL3 libglew_static glm::glm  ${ENGINE_NAME})
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        find_package(PkgConfig REQUIRED)
        pkg_check_modules (GTK2 REQUIRED gtk+-2.0)
        target_include_directories(${EDITOR_NAME} PRIVATE  ${GTK2_INCLUDE_DIRS})
        target_link_libraries(${EDITOR_NAME} nlohmann_json::nlohmann_json SDL3_image::SDL3_image SDL3::SDL3 libglew_static glm::glm ${GTK2_LIBRARIES} ${ENGINE_NAME})
endif ()
target_include_directories(${EDITOR_NAME} PRIVATE ${IMGUI_INCLUDE_DIR})
target_include_directories(${EDITOR_NAME} PRIVATE ${PARENT_DIR}/engine/src)



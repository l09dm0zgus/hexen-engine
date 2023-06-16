cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(${EDITOR_NAME} nlohmann_json::nlohmann_json SDL3::SDL3 SDL3_image glm::glm  HexenEngine)
    target_sources(${EDITOR_NAME} PRIVATE
            WindowsFileDialog.h
            WindowsFileDialog.cpp
            )
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules (GTK2 REQUIRED gtk+-2.0)
    target_include_directories(${EDITOR_NAME} PRIVATE  ${GTK2_INCLUDE_DIRS})
    target_link_libraries(${EDITOR_NAME} nlohmann_json::nlohmann_json SDL3::SDL3 SDL3_image glm::glm ${GTK2_LIBRARIES} HexenEngine)

    target_sources(${EDITOR_NAME} PRIVATE
            GtkFileDialog.h
            GtkFileDialog.cpp
            )
endif ()

target_sources(${EDITOR_NAME} PRIVATE
      FileDialog.h
      FileDialog.cpp
      INativeFileDialog.h
        )
cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})

set(CMAKE_CXX_STANDARD 17)
add_executable(${EDITOR_NAME})

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(${EDITOR_NAME} nlohmann_json::nlohmann_json SDL3-static SDL3_image glm::glm  HexenEngine)
    target_sources(${EDITOR_NAME} PRIVATE main.cpp
            gui/editors_windows/native_file_dialog/WindowsFileDialog.h
            gui/editors_windows/native_file_dialog/WindowsFileDialog.cpp
            )
    add_compile_definitions(IS_WINDOWS)
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    find_package(PkgConfig REQUIRED)
  pkg_check_modules (GTK2 REQUIRED gtk+-2.0)
  target_include_directories(${EDITOR_NAME} PRIVATE  ${GTK2_INCLUDE_DIRS})
  target_link_libraries(${EDITOR_NAME} nlohmann_json::nlohmann_json SDL3-static SDL3_image glm::glm ${GTK2_LIBRARIES} HexenEngine)

   target_sources(${EDITOR_NAME} PRIVATE main.cpp
          gui/editors_windows/native_file_dialog/GtkFileDialog.h
          gui/editors_windows/native_file_dialog/GtkFileDialog.cpp
           )
    add_compile_definitions(IS_UNIX)
endif ()

target_sources(${EDITOR_NAME} PRIVATE main.cpp
        application/Application.cpp
        application/Application.h
        gui/EditorGUI.cpp
        gui/EditorGUI.h
        gui/Style.h
        gui/Style.cpp
        gui/editors_windows/SceneWindow.h
        gui/editors_windows/SceneWindow.cpp
        gui/Dockspace.h
        gui/Dockspace.cpp
        gui/editors_windows/GUIWindow.cpp
        gui/editors_windows/GUIWindow.h
        gui/editors_windows/MainMenuBar.h
        gui/editors_windows/MainMenuBar.cpp
        gui/editors_windows/native_file_dialog/INativeFileDialog.h
        gui/editors_windows/native_file_dialog/FileDialog.h
        gui/editors_windows/native_file_dialog/FileDialog.cpp
        )

target_include_directories(${EDITOR_NAME} PRIVATE ${PARENT_DIR}/engine/src)
target_include_directories(${EDITOR_NAME} PRIVATE ${SDL_IMAGE_INCLUDE_DIR})
target_include_directories(${EDITOR_NAME} PRIVATE ${GLM_INCLUDE_DIR})
target_include_directories(${EDITOR_NAME} PRIVATE ${SDL_INCLUDE_DIR})
target_include_directories(${EDITOR_NAME} PRIVATE ${IMGUI_INCLUDE_DIR})
target_include_directories(${EDITOR_NAME} PRIVATE ${GLEW_INCLUDE_DIR})
target_include_directories(${EDITOR_NAME} PRIVATE ${JSON_INCLUDE_DIR})



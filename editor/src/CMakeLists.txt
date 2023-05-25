cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})

set(CMAKE_CXX_STANDARD 17)
add_executable(${EDITOR_NAME})

target_sources(${EDITOR_NAME} PRIVATE main.cpp
        application/Application.cpp
        application/Application.h
        gui/EditorGUI.cpp
        gui/EditorGUI.h)


target_include_directories(${EDITOR_NAME} PRIVATE ${PARENT_DIR}/engine/src)
target_include_directories(${EDITOR_NAME} PRIVATE ${SDL_IMAGE_INCLUDE_DIR})
target_include_directories(${EDITOR_NAME} PRIVATE ${GLM_INCLUDE_DIR})
target_include_directories(${EDITOR_NAME} PRIVATE ${SDL_INCLUDE_DIR})
target_include_directories(${EDITOR_NAME} PRIVATE ${IMGUI_INCLUDE_DIR})
target_include_directories(${EDITOR_NAME} PRIVATE ${GLEW_INCLUDE_DIR})

target_link_libraries(${EDITOR_NAME} nlohmann_json::nlohmann_json SDL3-static SDL3_image glm::glm  HexenEngine)
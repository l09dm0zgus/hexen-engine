cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})

set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${PARENT_DIR}/engine/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL_IMAGE_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json SDL3-shared SDL3_image glm::glm)
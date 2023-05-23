cmake_minimum_required(VERSION 3.6)

project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

find_library(SDL3 SDL3)
find_library(OpenGL OpenGL)
find_library(glm glm)

option(BUILD_ANDROID "Build android binary" OFF)


if(BUILD_ANDROID)
    add_library(${PROJECT_NAME} SHARED)
else()
    add_executable(${PROJECT_NAME})
endif(BUILD_ANDROID)

target_sources(${PROJECT_NAME} PRIVATE main.cpp)

add_subdirectory(components)
add_subdirectory(core)
add_subdirectory(entity)

include_directories(${SDL_IMAGE_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${SDL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}  SDL3-shared SDL3_image GLESv3 glm)


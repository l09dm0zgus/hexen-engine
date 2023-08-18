cmake_minimum_required(VERSION 3.6)

project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

find_library(SDL3 SDL3)
find_library(OpenGL OpenGL)
find_library(glm glm)


if(BUILD_LIB)
    add_library(${PROJECT_NAME} STATIC)
elseif (BUILD_ANDROID)
    add_library(${PROJECT_NAME} SHARED)
    target_sources(${PROJECT_NAME} PRIVATE main.cpp)
else ()
    add_executable(${PROJECT_NAME})
    target_sources(${PROJECT_NAME} PRIVATE main.cpp)
endif(BUILD_LIB)

add_definitions(-DTRACY_ENABLE=1)

add_subdirectory(components)
add_subdirectory(core)
add_subdirectory(entity)
add_subdirectory(systems)
add_subdirectory(profiling)

include_directories(${SDL_IMAGE_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${SDL_INCLUDE_DIR})
include_directories(${JSON_INCLUDE_DIR})
include_directories(${CONTEXT_INCLUDE_DIR})

if (${BUILD_ANDROID} STREQUAL  OFF)
    include_directories(${GLEW_INCLUDE_DIR})
endif ()
if (BUILD_ANDROID)
    target_link_libraries(${PROJECT_NAME}  SDL3::SDL3 SDL3_image GLESv3 boost_context glm)
else()
    target_link_libraries(${PROJECT_NAME} SDL3::SDL3 SDL3_image libglew_static boost_context glm)
endif (BUILD_ANDROID)

cmake_minimum_required(VERSION 3.6)

project(${PROJECT_NAME})

add_subdirectory(glm)
add_subdirectory(SDL)
add_subdirectory(SDL_image)
add_subdirectory(json)
add_subdirectory(fiber)
add_subdirectory(assert)
add_subdirectory(config)
add_subdirectory(context)
add_subdirectory(core)

if (${BUILD_ANDROID} STREQUAL  OFF)
    add_subdirectory(glew-cmake)
endif ()

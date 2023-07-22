cmake_minimum_required(VERSION 3.6)
option(BUILD_ANDROID "Build android binary" OFF)
option(BUILD_LIB "Build as static lib" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


if (BUILD_ANDROID)
    set(PROJECT_NAME main)
else ()
    set(PROJECT_NAME HexenEngine)
endif (BUILD_ANDROID)

project(${PROJECT_NAME})

    # armeabi-v7a requires cpufeatures library
# include(AndroidNdkModules)
# android_ndk_import_module_cpufeatures()
set(SDL_IMAGE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/SDL_image/include/SDL3)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/glm)
set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/SDL/include)
set(JSON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/json/include)
set(CONTEXT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/boost_context/include)

if (${BUILD_ANDROID} STREQUAL  OFF)
    set(GLEW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/glew-cmake/include)
endif ()


add_subdirectory(src)
add_subdirectory(submodules)
# Your game and its CMakeLists.txt are in a subfolder named "src"



cmake_minimum_required(VERSION 3.6)

set(PROJECT_NAME Game)
project(${PROJECT_NAME})

# armeabi-v7a requires cpufeatures library
# include(AndroidNdkModules)
# android_ndk_import_module_cpufeatures()
set(SDL_IMAGE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/SDL_image)
add_subdirectory(src)
add_subdirectory(submodules)
# Your game and its CMakeLists.txt are in a subfolder named "src"



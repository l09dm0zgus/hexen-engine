cmake_minimum_required(VERSION 3.6)
if(BUILD_ANDROID)
    set(PROJECT_NAME main)
else()
    set(PROJECT_NAME Battleblaze)
endif(BUILD_ANDROID)
project(${PROJECT_NAME})

# armeabi-v7a requires cpufeatures library
# include(AndroidNdkModules)
# android_ndk_import_module_cpufeatures()
set(SDL_IMAGE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/SDL_image/include/SDL3)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/glm)
set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/SDL/include)


add_subdirectory(src)
add_subdirectory(submodules)
# Your game and its CMakeLists.txt are in a subfolder named "src"



cmake_minimum_required(VERSION 3.6)

set(PROJECT_NAME Game)
project(${PROJECT_NAME})

# armeabi-v7a requires cpufeatures library
# include(AndroidNdkModules)
# android_ndk_import_module_cpufeatures()
add_subdirectory(submodules/SDL)
#add_subdirectory(submodules/SDL_image)
add_subdirectory(submodules/glm)

# Your game and its CMakeLists.txt are in a subfolder named "src"
add_subdirectory(src)


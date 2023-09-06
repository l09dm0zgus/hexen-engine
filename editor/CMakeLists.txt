cmake_minimum_required(VERSION 3.20)

cmake_path(GET  CMAKE_CURRENT_SOURCE_DIR PARENT_PATH PARENT_DIR)
add_subdirectory(${PARENT_DIR}/engine/ engine_build)

add_subdirectory(src)
add_subdirectory(submodules)

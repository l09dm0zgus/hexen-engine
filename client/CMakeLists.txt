cmake_minimum_required(VERSION 3.20)
project(Client)

set(GAME_NAME "Game" CACHE STRING "Game")

if(${BUILD_FOR_ANDROID})
    add_library(${GAME_NAME})
else ()
    add_executable(${GAME_NAME})
endif (${BUILD_FOR_ANDROID})

cmake_path(GET  CMAKE_CURRENT_SOURCE_DIR PARENT_PATH PARENT_DIR)
add_subdirectory(${PARENT_DIR}/engine/ engine_build)

add_subdirectory(src)

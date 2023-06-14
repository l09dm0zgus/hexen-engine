cmake_minimum_required(VERSION 3.6)

option(BUIILD_EDITOR "Build editor" OFF)

if(BUILD_EDITOR)
add_subdirectory(editor)
endif()
add_subdirectory(engine)

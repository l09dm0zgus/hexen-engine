cmake_minimum_required(VERSION 3.20)
project(Hexen)

if (NOT TARGET Profiling)
    add_library(Profiling SHARED)
endif (NOT TARGET Profiling)

file(GLOB SRC_FILES
        "*.cpp"
        "*.hpp"
        "*.h"
)

target_sources(Profiling PRIVATE
        ${SRC_FILES}
)
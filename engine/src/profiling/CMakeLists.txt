cmake_minimum_required(VERSION 3.20)
project(Hexen)

message(STATUS "Engine Name:" ${ENGINE_NAME})

file(GLOB SRC_FILES
        "*.cpp"
        "*.hpp"
        "*.h"
)

target_sources(${ENGINE_NAME} PRIVATE
        ${SRC_FILES}
)
cmake_minimum_required(VERSION 3.6)
project(${PROJECT_NAME})

file(GLOB SRC_FILES
        "*.cpp"
        "*.hpp"
        "*.h"
)

target_sources(${PROJECT_NAME} PRIVATE
        ${SRC_FILES}
)
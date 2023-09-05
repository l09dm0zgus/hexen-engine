cmake_minimum_required(VERSION 3.6)


file(GLOB SRC_FILES
        "*.cpp"
        "*.hpp"
        "*.h"
)

target_sources(${ENGINE_NAME} PRIVATE
        ${SRC_FILES}
)
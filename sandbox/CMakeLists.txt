cmake_minimum_required(VERSION 3.20)
project(sandbox)

add_executable(sandbox Sandbox.cpp)
target_include_directories(sandbox PRIVATE GRAPHICS_INCLUDE_DIR)
target_link_libraries(sandbox PRIVATE ${RENDER_ENGINE_NAME})

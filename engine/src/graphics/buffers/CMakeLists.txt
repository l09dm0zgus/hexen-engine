cmake_minimum_required(VERSION 3.20)
project(Hexen)

target_sources(${RENDER_ENGINE_NAME} PUBLIC
        Buffers.hpp
        Buffers.cpp
        RectangleVertices.hpp
)

if (ENABLE_OPENGL_SUPPORT)
    add_subdirectory(GL)
endif ()
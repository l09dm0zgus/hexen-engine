cmake_minimum_required(VERSION 3.20)
project(RenderingEngine)
target_sources(${RENDER_MODULE_NAME} PUBLIC
        RenderContext.hpp
        RenderContext.cpp
)


if (ENABLE_OPENGL_SUPPORT)
    add_subdirectory(GL)
endif ()
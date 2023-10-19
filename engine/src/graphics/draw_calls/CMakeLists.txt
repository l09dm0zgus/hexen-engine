cmake_minimum_required(VERSION 3.20)
project(RenderingEngine)

target_sources(${RENDER_MODULE_NAME} PUBLIC
        DrawCalls.hpp
)

if (ENABLE_OPENGL_SUPPORT)
    add_subdirectory(GL_draw_calls)
endif ()
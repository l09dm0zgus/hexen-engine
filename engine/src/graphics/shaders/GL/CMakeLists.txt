cmake_minimum_required(VERSION 3.20)
project(RenderingEngine)
target_sources(${RENDER_ENGINE_NAME} PUBLIC
        GLShaderProgram.hpp
        GLShaderProgram.cpp
)

if (ENABLE_OPENGL_SUPPORT)
    #add_subdirectory(GL)
endif ()
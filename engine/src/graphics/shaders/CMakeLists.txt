cmake_minimum_required(VERSION 3.20)
project(RenderingEngine)
target_sources(${RENDER_ENGINE_NAME} PUBLIC
        ShaderFile.hpp
        ShaderFile.cpp
        ShaderProgram.hpp
        ShaderProgram.cpp
)
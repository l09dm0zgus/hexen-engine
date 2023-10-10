cmake_minimum_required(VERSION 3.20)
project(RenderingEngine)

target_sources(${RENDER_MODULE_NAME} PUBLIC
        GLRenderContext.hpp
        GLRenderContext.cpp
)
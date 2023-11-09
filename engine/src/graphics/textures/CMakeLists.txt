cmake_minimum_required(VERSION 3.20)
project(RenderingEngine)

target_sources(${RENDER_MODULE_NAME} PUBLIC
        Texture.hpp
        Texture.cpp
        ImageAsset.hpp
        ImageAsset.cpp
)

if (ENABLE_OPENGL_SUPPORT)
    add_subdirectory(GL)
endif ()
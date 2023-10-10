cmake_minimum_required(VERSION 3.20)
project(Hexen)

message(STATUS "Engine Name:" ${ENGINE_NAME})

target_sources(${ENGINE_NAME} PRIVATE
        ../../graphics/shaders/ShaderFile.hpp
        ../../graphics/shaders/ShaderFile.cpp
        ../../graphics/shaders/GL/GLShaderProgram.hpp
        ../../graphics/shaders/GL/GLShaderProgram.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/Shaders.hpp
        ../../graphics/textures/GL/GLTexture2D.hpp
        ../../graphics/textures/GL/GLTexture2D.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture/FrameBufferTexture.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture/FrameBufferTexture.cpp
        )
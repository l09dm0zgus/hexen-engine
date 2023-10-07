cmake_minimum_required(VERSION 3.20)
project(Hexen)

message(STATUS "Engine Name:" ${ENGINE_NAME})

target_sources(${ENGINE_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ShaderFile.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ShaderFile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ShaderProgram.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ShaderProgram.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/Shaders.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture/Texture.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture/Texture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture/FrameBufferTexture.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture/FrameBufferTexture.cpp
        )
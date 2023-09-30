cmake_minimum_required(VERSION 3.20)
project(Hexen)

message(STATUS "Engine Name:" ${ENGINE_NAME})

target_sources(${ENGINE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ElementsBufferObject.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ElementsBufferObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Graphics.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RectangleData.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexArrayObject.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexArrayObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexAttributes.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexAttributes.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexBufferObject.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexBufferObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ShaderFile.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ShaderFile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ShaderProgram.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ShaderProgram.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/Shaders.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture/Texture.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture/Texture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture/FrameBufferTexture.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture/FrameBufferTexture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FrameBufferObject.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FrameBufferObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderBufferObject.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderBufferObject.cpp
        )
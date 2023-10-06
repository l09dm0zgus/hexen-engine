cmake_minimum_required(VERSION 3.20)
project(Hexen)

message(STATUS "Engine Name:" ${ENGINE_NAME})

target_sources(${ENGINE_NAME} PRIVATE ../../graphics/buffers/GL/GLElementsBuffer.hpp
        ../../graphics/buffers/GL/GLElementsBuffer.cpp
        ../../graphics/buffers/GL/Graphics.hpp
        ../../graphics/buffers/RectangleVertices.hpp
        ../../graphics/buffers/GL/GLVertexArrayObject.hpp
        ../../graphics/buffers/GL/GLVertexArrayObject.cpp
        ../../graphics/buffers/GL/GLVertexAttributes.hpp
        ../../graphics/buffers/GL/GLVertexAttributes.cpp
        ../../graphics/buffers/GL/GLVertexBufferObject.hpp
        ../../graphics/buffers/GL/GLVertexBufferObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ShaderFile.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ShaderFile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ShaderProgram.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ShaderProgram.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/Shaders.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture/Texture.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture/Texture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture/FrameBufferTexture.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture/FrameBufferTexture.cpp
        ../../graphics/buffers/GL/GLFrameBufferObject.hpp
        ../../graphics/buffers/GL/GLFrameBufferObject.cpp
        ../../graphics/buffers/GL/GLRenderBufferObject.hpp
        ../../graphics/buffers/GL/GLRenderBufferObject.cpp
        )
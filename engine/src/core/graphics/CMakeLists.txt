cmake_minimum_required(VERSION 3.6)

target_sources(${ENGINE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ElementsBufferObject.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ElementsBufferObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Graphics.h
        ${CMAKE_CURRENT_SOURCE_DIR}/RectangleData.h
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexArrayObject.h
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexArrayObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexAttributes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexAttributes.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexBufferObject.h
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexBufferObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ShaderFile.h
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ShaderFile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ShaderProgram.h
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ShaderProgram.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/Shaders.h
        ${CMAKE_CURRENT_SOURCE_DIR}/texture/Texture.h
        ${CMAKE_CURRENT_SOURCE_DIR}/texture/Texture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/texture/FrameBufferTexture.h
        ${CMAKE_CURRENT_SOURCE_DIR}/texture/FrameBufferTexture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FrameBufferObject.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FrameBufferObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderBufferObject.h
        ${CMAKE_CURRENT_SOURCE_DIR}/RenderBufferObject.cpp
        )
cmake_minimum_required(VERSION 3.20)
project(Hexen)

target_sources(${RENDER_MODULE_NAME} PUBLIC
        GLElementsBuffer.hpp
        GLElementsBuffer.cpp
        GLVertexBuffer.hpp
        GLVertexBuffer.cpp
        GLFrameBuffer.hpp
        GLFrameBuffer.cpp
        GLRenderBuffer.hpp
        GLRenderBuffer.cpp
        GLVertexArray.hpp
        GLVertexArray.cpp
        GlUniformBuffer.hpp
        GlUniformBuffer.cpp)

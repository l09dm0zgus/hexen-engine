cmake_minimum_required(VERSION 3.20)
project(RenderingEngine)

target_sources(${RENDER_MODULE_NAME} PUBLIC
        IRenderCommand.hpp
        FramebufferCommand.hpp
        FramebufferCommand.cpp
        RenderPipeline.hpp
        RenderPipeline.cpp
        ClearCommand.hpp
        ClearCommand.cpp
        ViewportCommand.hpp
        ViewportCommand.cpp
)

if (ENABLE_OPENGL_SUPPORT)
    add_subdirectory(GL_subcommands)
endif ()
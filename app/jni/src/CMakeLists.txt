cmake_minimum_required(VERSION 3.6)

project(${PROJECT_NAME})
#find_library(SDL2_image SDL2_image)
find_library(SDL2 SDL2)

find_library(OpenGL OpenGL)
find_library(glm glm)

add_library(main SHARED)

target_sources(main PRIVATE main.cpp
        core/window/Window.cpp
        core/window/Window.h
        core/application/Application.h
        core/application/Application.cpp
        core/graphics/RectangleVertices.h
        core/graphics/RectangleVertices.cpp
        core/graphics/VertexBufferObject.h
        core/graphics/VertexBufferObject.cpp
        core/graphics/ShaderFile.h
        core/graphics/ShaderFile.cpp
        core/graphics/ShaderProgram.h
        core/graphics/ShaderProgram.cpp
        )
target_link_libraries(main SDL2 GLESv2 glm)


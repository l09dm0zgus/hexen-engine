cmake_minimum_required(VERSION 3.6)

project(${PROJECT_NAME})

find_library(SDL3 SDL3)
find_library(OpenGL OpenGL)
find_library(glm glm)

add_library(main SHARED)

target_sources(main PRIVATE main.cpp
        core/window/Window.cpp
        core/window/Window.h
        core/application/Application.h
        core/application/Application.cpp
        core/graphics/RectangleVertices.h
        core/graphics/VertexBufferObject.h
        core/graphics/VertexBufferObject.cpp
        core/graphics/shaders/ShaderFile.h
        core/graphics/shaders/ShaderFile.cpp
        core/graphics/shaders/ShaderProgram.h
        core/graphics/shaders/ShaderProgram.cpp
        core/graphics/VertexAttributes.h
        core/graphics/VertexAttributes.cpp
        core/graphics/VertexArrayObject.h
        core/graphics/VertexArrayObject.cpp
        components/graphics/SpriteComponent.h
        components/graphics/SpriteComponent.cpp
        components/graphics/SpriteInstancedComponent.h
        components/graphics/SpriteInstancedComponent.cpp
        core/graphics/texture/Texture.h
        core/graphics/texture/Texture.cpp
        core/transform/Transform.h
        core/transform/Transform.cpp
        core/camera/Camera.h
        core/camera/Camera.cpp
        components/IComponent.h
        components/graphics/RenderComponent.h
        components/graphics/RenderComponent.cpp
        pool/BasePool.h
        pool/BaseComponentPool.h
        pool/graphics/texture/TexturesPool.h
        pool/graphics/texture/TexturesPool.cpp
        pool/graphics/SpriteComponentsPool.h
        pool/graphics/SpriteComponentsPool.cpp
        pool/graphics/SpriteInstancedComponentPool.h
        pool/graphics/SpriteInstancedComponentPool.cpp
        core/uuid/uuid.h
        )
include_directories(${SDL_IMAGE_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
target_link_libraries(main SDL3 SDL3_image GLESv3 glm)


cmake_minimum_required(VERSION 3.6)

project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

find_library(SDL3 SDL3)
find_library(OpenGL OpenGL)
find_library(glm glm)



add_library(main SHARED)

target_sources(main PRIVATE main.cpp
        core/window/Window.cpp
        core/window/Window.h
        core/application/Application.h
        core/application/Application.cpp
        core/graphics/RectangleData.h
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
        core/graphics/ElementsBufferObject.h
        core/graphics/ElementsBufferObject.cpp
        components/graphics/SpriteComponent.h
        components/graphics/SpriteComponent.cpp
        components/graphics/SpriteInstancedComponent.h
        components/graphics/SpriteInstancedComponent.cpp
        core/graphics/texture/Texture.h
        core/graphics/texture/Texture.cpp
        components/camera/CameraComponent.h
        components/camera/CameraComponent.cpp
        components/Component.h
        components/graphics/RenderComponent.h
        components/graphics/RenderComponent.cpp
        components/transform/TransformComponent.h
        components/transform/TransformComponent.cpp
        core/uuid/uuid.h
        core/Types.h
        core/memory_pool/MemoryPool.h
        core/memory_pool/MemoryPool.cpp
        core/memory_pool/AllocatedObject.h
        core/memory_pool/AllocatedObject.cpp
        core/exceptions/ComponentNotFound.h
        core/exceptions/ComponentNotFound.cpp
        entity/Entity.h
        entity/Entity.cpp
        entity/scene/SceneEntity.h
        entity/scene/SceneEntity.cpp
        )
include_directories(${SDL_IMAGE_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})

target_link_libraries(main  SDL3 SDL3_image GLESv3 glm)


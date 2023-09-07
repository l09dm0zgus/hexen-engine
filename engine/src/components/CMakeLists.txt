
cmake_minimum_required(VERSION 3.6)

target_sources(${ENGINE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/camera/CameraComponent.hpp
         ${CMAKE_CURRENT_SOURCE_DIR}/camera/CameraComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/graphics/RenderComponent.hpp
         ${CMAKE_CURRENT_SOURCE_DIR}/graphics/RenderComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/graphics/SpriteComponent.hpp
         ${CMAKE_CURRENT_SOURCE_DIR}/graphics/SpriteComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/graphics/SpriteInstancedComponent.hpp
         ${CMAKE_CURRENT_SOURCE_DIR}/graphics/SpriteInstancedComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/transform/TransformComponent.hpp
         ${CMAKE_CURRENT_SOURCE_DIR}/transform/TransformComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Component.hpp)

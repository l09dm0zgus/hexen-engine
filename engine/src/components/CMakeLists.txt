
cmake_minimum_required(VERSION 3.6)

target_sources(${ENGINE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/camera/CameraComponent.h
         ${CMAKE_CURRENT_SOURCE_DIR}/camera/CameraComponent.cpp
         ${CMAKE_CURRENT_SOURCE_DIR}/graphics/RenderComponent.h
         ${CMAKE_CURRENT_SOURCE_DIR}/graphics/RenderComponent.cpp
         ${CMAKE_CURRENT_SOURCE_DIR}/graphics/SpriteComponent.h
         ${CMAKE_CURRENT_SOURCE_DIR}/graphics/SpriteComponent.cpp
         ${CMAKE_CURRENT_SOURCE_DIR}/graphics/SpriteInstancedComponent.h
         ${CMAKE_CURRENT_SOURCE_DIR}/graphics/SpriteInstancedComponent.cpp
         ${CMAKE_CURRENT_SOURCE_DIR}/transform/TransformComponent.h
         ${CMAKE_CURRENT_SOURCE_DIR}/transform/TransformComponent.cpp
         ${CMAKE_CURRENT_SOURCE_DIR}/Component.h)

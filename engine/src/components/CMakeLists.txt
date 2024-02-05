
cmake_minimum_required(VERSION 3.20)
project(Hexen)
if(NOT TARGET ${COMPONENTS_MODULE_NAME})
    add_library(${COMPONENTS_MODULE_NAME} STATIC)
endif (NOT TARGET ${COMPONENTS_MODULE_NAME})

target_sources(${COMPONENTS_MODULE_NAME} PRIVATE camera/CameraComponent.hpp camera/CameraComponent.cpp
        graphics/SpriteComponent.hpp
        graphics/SpriteComponent.cpp
        graphics/TilesetAsset.cpp
        graphics/TilesetAsset.hpp
        transform/TransformComponent.hpp
        transform/TransformComponent.cpp
        Component.hpp
        ComponentContainer.hpp)

target_include_directories(${COMPONENTS_MODULE_NAME} PRIVATE ${CORE_ENGINE_INCLUDE_DIR})
target_include_directories(${COMPONENTS_MODULE_NAME} PRIVATE ${RENDER_ENGINE_INCLUDE_DIR})
target_include_directories(${COMPONENTS_MODULE_NAME} PRIVATE ${THREADING_ENGINE_INCLUDE_DIR})

target_link_libraries(${COMPONENTS_MODULE_NAME} PUBLIC ${CORE_MODULE_NAME} ${RENDER_MODULE_NAME})

if(MSVC)
    target_compile_options(${COMPONENTS_MODULE_NAME} PRIVATE /W4)
else()
    target_compile_options(${COMPONENTS_MODULE_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
cmake_minimum_required(VERSION 3.20)
project(Hexen)

option(ENABLE_OPENGL_SUPPORT "Enable OpenFL API for rendering" ON)
option(ENABLE_VULKAN_SUPPORT "Enable Vulkan API for rendering" OFF)
option(RENDER_ENGINE_STATIC "Compile Render Engine as static" OFF)
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH PARENT_DIR)

if (WIN32)
    option(ENABLE_DIRECTX12_SUPPORT "Enable DirectX12 API for rendering" OFF)
endif (WIN32)

set(RENDER_ENGINE_NAME RenderingEngine)
if(NOT TARGET ${RENDER_ENGINE_NAME})

    if(RENDER_ENGINE_STATIC)
        add_library(${RENDER_ENGINE_NAME} STATIC)
    else ()
        add_library(${RENDER_ENGINE_NAME} SHARED)
    endif (RENDER_ENGINE_STATIC)
endif (NOT TARGET ${RENDER_ENGINE_NAME})

set_target_properties(${RENDER_ENGINE_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if(ENABLE_VULKAN_SUPPORT)
    target_compile_definitions(${RENDER_ENGINE_NAME} PUBLIC _ENABLE_VULKAN_SUPPORT)
endif (ENABLE_VULKAN_SUPPORT)

if (ENABLE_OPENGL_SUPPORT)
    target_compile_definitions(${RENDER_ENGINE_NAME} PUBLIC _ENABLE_OPENGL_SUPPORT)
    target_link_libraries(${RENDER_ENGINE_NAME} PUBLIC libglew_static)
endif ()

if (WIN32)
    if (ENABLE_DIRECTX12_SUPPORT)
        target_compile_definitions(${RENDER_ENGINE_NAME} PUBLIC _ENABLE_DIRECTX12_SUPPORT)
    endif (ENABLE_DIRECTX12_SUPPORT)
endif (WIN32)

cmake_path(GET  CMAKE_CURRENT_SOURCE_DIR PARENT_PATH PARENT_DIR)
MESSAGE(STATUS ${PARENT_DIR})
target_include_directories(${RENDER_ENGINE_NAME} PUBLIC ${PARENT_DIR}/core)
target_include_directories(${RENDER_ENGINE_NAME} PUBLIC ${SDL_INCLUDE_DIR})
add_subdirectory(render_context)
add_subdirectory(buffers)
add_subdirectory(textures)
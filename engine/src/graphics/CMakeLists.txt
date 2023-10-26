cmake_minimum_required(VERSION 3.20)
project(Hexen)

option(ENABLE_OPENGL_SUPPORT "Enable OpenFL API for rendering" ON)
option(ENABLE_VULKAN_SUPPORT "Enable Vulkan API for rendering" OFF)
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH PARENT_DIR)

if (WIN32)
    option(ENABLE_DIRECTX12_SUPPORT "Enable DirectX12 API for rendering" OFF)
endif (WIN32)

if(NOT TARGET ${RENDER_MODULE_NAME})

    add_library(${RENDER_MODULE_NAME} STATIC)

endif (NOT TARGET ${RENDER_MODULE_NAME})

set_target_properties(${RENDER_MODULE_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if(ENABLE_VULKAN_SUPPORT)
    target_compile_definitions(${RENDER_MODULE_NAME} PUBLIC _ENABLE_VULKAN_SUPPORT)
endif (ENABLE_VULKAN_SUPPORT)

if (ENABLE_OPENGL_SUPPORT)
    target_compile_definitions(${RENDER_MODULE_NAME} PUBLIC _ENABLE_OPENGL_SUPPORT)
    target_link_libraries(${RENDER_MODULE_NAME} PUBLIC ${CORE_MODULE_NAME} opengl32)
    target_link_libraries(${RENDER_MODULE_NAME} PUBLIC libglew_static)

endif ()

if (WIN32)
    if (ENABLE_DIRECTX12_SUPPORT)
        target_compile_definitions(${RENDER_MODULE_NAME} PUBLIC _ENABLE_DIRECTX12_SUPPORT)
    endif (ENABLE_DIRECTX12_SUPPORT)
endif (WIN32)

target_include_directories(${RENDER_MODULE_NAME} PUBLIC ${CORE_ENGINE_INCLUDE_DIR})
target_include_directories(${RENDER_MODULE_NAME} PUBLIC ${SDL_INCLUDE_DIR})
target_include_directories(${RENDER_MODULE_NAME} PUBLIC ${GLM_INCLUDE_DIR})
target_include_directories(${RENDER_MODULE_NAME} PUBLIC ${SDL_IMAGE_INCLUDE_DIR})
target_include_directories(${RENDER_MODULE_NAME} PUBLIC ${JSON_INCLUDE_DIR})
target_include_directories(${RENDER_MODULE_NAME} PUBLIC ${PHMAP_INCLUDE_DIR})

add_subdirectory(render_context)
add_subdirectory(buffers)
add_subdirectory(textures)
add_subdirectory(shaders)
add_subdirectory(render_commands)
add_subdirectory(draw_calls)

if(MSVC)
    target_compile_options(${RENDER_MODULE_NAME} PRIVATE /W4)
else()
    target_compile_options(${RENDER_MODULE_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
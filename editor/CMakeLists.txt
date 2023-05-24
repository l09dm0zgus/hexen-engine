cmake_minimum_required(VERSION 3.20)
set(EDITOR_NAME HexenEditor)
project(${EDITOR_NAME})

cmake_path(GET  CMAKE_CURRENT_SOURCE_DIR PARENT_PATH PARENT_DIR)

set(IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/imgui)
set(SDL_IMAGE_INCLUDE_DIR ${PARENT_DIR}/engine/submodules/SDL_image/include/SDL3)
set(GLM_INCLUDE_DIR ${PARENT_DIR}/engine/submodules/glm)
set(SDL_INCLUDE_DIR ${PARENT_DIR}/engine/submodules/SDL/include)
set(GLEW_INCLUDE_DIR ${PARENT_DIR}/engine/submodules/glew-cmake/include)

add_subdirectory(${PARENT_DIR}/engine/ engine_build)

set(JSON_BuildTests OFF CACHE INTERNAL "")


add_subdirectory(src)
#add_subdirectory(submodules/imgui)

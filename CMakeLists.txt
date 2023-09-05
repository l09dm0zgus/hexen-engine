cmake_minimum_required(VERSION 3.6)
project(Hexen)

set(CMAKE_CXX_STANDARD 17)
set(EDITOR_NAME HexenEditor CACHE INTERNAL "")
set(ENGINE_NAME HexenEngine CACHE INTERNAL "")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option(BUILD_EDITOR "Build editor" ON)
option(BUILD_SHARED "Build as shared lib" OFF)
option(BUILD_STATIC "Build as static lib" ON)
option(BUILD_ANDROID "Build as Android" OFF)
option(ENABLE_PROFILING OFF)

if(BUILD_STATIC)
    add_library(${ENGINE_NAME} STATIC)
    add_subdirectory(engine)
elseif(BUILD_SHARED)
    add_library(${ENGINE_NAME} SHARED)
    add_subdirectory(engine)
endif()

if (${BUILD_ANDROID} STREQUAL  OFF)

endif ()

if (BUILD_ANDROID)
    target_link_libraries(${ENGINE_NAME}   SDL3::SDL3 SDL3_image GLESv3 boost_context glm)
else()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/engine/submodules/glew-cmake)
    set(GLEW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/engine/submodules/glew-cmake/include)
    include_directories(${GLEW_INCLUDE_DIR})
    target_link_libraries(${ENGINE_NAME}  SDL3::SDL3 SDL3_image libglew_static boost_context glm)
endif (BUILD_ANDROID)

set(SDL_IMAGE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/engine/submodules/SDL_image/include/SDL3)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/engine/submodules/glm)
set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/engine/submodules/SDL/include)
set(JSON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/engine/submodules/json/include)
set(CONTEXT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/engine/submodules/boost_context/include)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/engine/submodules/glm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/engine/submodules/SDL EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/engine/submodules/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/engine/submodules/json)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/engine/submodules/boost_context)

include_directories(${SDL_IMAGE_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${SDL_INCLUDE_DIR})
include_directories(${IMGUI_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${JSON_INCLUDE_DIR})
include_directories(${CONTEXT_INCLUDE_DIR})

if (${ENABLE_PROFILING})
        add_definitions(-DTRACY_ENABLE=1)
        if(WIN32)
                target_link_libraries(${EDITOR_NAME}  wsock32 ws2_32 -ldbghelp )
        endif()
endif()

if(BUILD_EDITOR)
	set(IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/editor/submodules/imgui)
	add_subdirectory(editor)
endif()



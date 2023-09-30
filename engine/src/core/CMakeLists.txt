cmake_minimum_required(VERSION 3.20)
project(Hexen)

message(STATUS "Engine Name:" ${ENGINE_NAME})
target_sources(${ENGINE_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/ComponentNotFound.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/ComponentNotFound.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/MappingNotFound.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/MappingNotFound.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/memory_pool/AllocatedObject.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/memory_pool/AllocatedObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/memory_pool/MemoryPool.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/memory_pool/MemoryPool.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/uuid/uuid.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/window/Window.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/window/Window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/scene/Scene.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/scene/Scene.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/scene/SceneManager.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/scene/SceneManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/scene/Grid.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/scene/Grid.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/application/GameLoop.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/application/GameLoop.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Types.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Serialization.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/application/Settings.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/application/Settings.cpp)

add_subdirectory(input_devices)
add_subdirectory(graphics)
add_subdirectory(threading)
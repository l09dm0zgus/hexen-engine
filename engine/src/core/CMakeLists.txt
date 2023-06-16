cmake_minimum_required(VERSION 3.6)
project(${PROJECT_NAME})


target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/application/Application.h
        ${CMAKE_CURRENT_SOURCE_DIR}/application/Application.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/ComponentNotFound.h
        ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/ComponentNotFound.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/memory_pool/AllocatedObject.h
        ${CMAKE_CURRENT_SOURCE_DIR}/memory_pool/AllocatedObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/memory_pool/MemoryPool.h
        ${CMAKE_CURRENT_SOURCE_DIR}/memory_pool/MemoryPool.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/uuid/uuid.h
        ${CMAKE_CURRENT_SOURCE_DIR}/window/Window.h
        ${CMAKE_CURRENT_SOURCE_DIR}/window/Window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/level/Level.h
        ${CMAKE_CURRENT_SOURCE_DIR}/level/Level.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Serialization.h
        )


add_subdirectory(graphics)

cmake_minimum_required(VERSION 3.6)

target_sources(${ENGINE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/application/Application.h
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
        ${CMAKE_CURRENT_SOURCE_DIR}/scene/Scene.h
        ${CMAKE_CURRENT_SOURCE_DIR}/scene/Scene.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/scene/SceneManager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/scene/SceneManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/scene/Grid.h
        ${CMAKE_CURRENT_SOURCE_DIR}/scene/Grid.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/application/GameLoop.h
        ${CMAKE_CURRENT_SOURCE_DIR}/application/GameLoop.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Serialization.h
        ${CMAKE_CURRENT_SOURCE_DIR}/application/Settings.h
        ${CMAKE_CURRENT_SOURCE_DIR}/application/Settings.cpp)

add_subdirectory(input_devices)
add_subdirectory(graphics)
add_subdirectory(threading)
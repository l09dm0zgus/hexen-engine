cmake_minimum_required(VERSION 3.20)
project(Hexen)

if(NOT TARGET ${CORE_NAME})

    add_library(${CORE_NAME} SHARED)

endif (NOT TARGET ${CORE_NAME})
target_include_directories(${CORE_NAME} PUBLIC ${GLM_INCLUDE_DIR})
target_include_directories(${CORE_NAME} PUBLIC ${SDL_INCLUDE_DIR})
target_include_directories(${CORE_NAME} PUBLIC ${SDL_IMAGE_INCLUDE_DIR})
target_include_directories(${CORE_NAME} PUBLIC ${JSON_INCLUDE_DIR})
target_include_directories(${CORE_NAME} PUBLIC ${CONTEXT_INCLUDE_DIR})
target_include_directories(${CORE_NAME} PUBLIC ${RENDER_ENGINE_INCLUDE_DIR})
target_include_directories(${CORE_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

message(WARNING "Render include: " ${RENDER_ENGINE_INCLUDE_DIR})
target_sources(${CORE_NAME} PUBLIC
        exceptions/ComponentNotFound.hpp
        exceptions/ComponentNotFound.cpp
        exceptions/MappingNotFound.hpp
        exceptions/MappingNotFound.cpp
        memory_pool/AllocatedObject.hpp
        memory_pool/AllocatedObject.cpp
        memory_pool/MemoryPool.hpp
        memory_pool/MemoryPool.cpp
        uuid/uuid.hpp
        window/Window.hpp
        window/Window.cpp
        #scene/Scene.hpp
        #scene/Scene.cpp
        #scene/SceneManager.hpp
        #scene/SceneManager.cpp
        #scene/Grid.hpp
        #scene/Grid.cpp
        #application/GameLoop.hpp
        #application/GameLoop.cpp
        Types.hpp
        Serialization.hpp
        application/Settings.hpp
        application/Settings.cpp)




add_subdirectory(input_devices)
add_subdirectory(threading)

target_link_libraries(${CORE_NAME} PUBLIC SDL3_image::SDL3_image SDL3::SDL3 nlohmann_json::nlohmann_json boost_context)
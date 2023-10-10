cmake_minimum_required(VERSION 3.20)
project(Hexen)

if(NOT TARGET ${CORE_MODULE_NAME})

    add_library(${CORE_MODULE_NAME} SHARED)

endif (NOT TARGET ${CORE_MODULE_NAME})

target_include_directories(${CORE_MODULE_NAME} PUBLIC ${GLM_INCLUDE_DIR})
target_include_directories(${CORE_MODULE_NAME} PUBLIC ${SDL_INCLUDE_DIR})
target_include_directories(${CORE_MODULE_NAME} PUBLIC ${SDL_IMAGE_INCLUDE_DIR})
target_include_directories(${CORE_MODULE_NAME} PUBLIC ${JSON_INCLUDE_DIR})
target_include_directories(${CORE_MODULE_NAME} PUBLIC ${CONTEXT_INCLUDE_DIR})
target_include_directories(${CORE_MODULE_NAME} PUBLIC ${RENDER_ENGINE_INCLUDE_DIR})
target_include_directories(${CORE_MODULE_NAME} PUBLIC ".")

target_sources(${CORE_MODULE_NAME} PUBLIC
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
        Types.hpp
        Serialization.hpp
        application/Settings.hpp
        application/Settings.cpp)




add_subdirectory(input_devices)
add_subdirectory(threading)

target_link_libraries(${CORE_MODULE_NAME} PUBLIC SDL3_image::SDL3_image SDL3::SDL3 nlohmann_json::nlohmann_json boost_context)

if(MSVC)
    target_compile_options(${CORE_MODULE_NAME} PRIVATE /W4)
else()
    target_compile_options(${CORE_MODULE_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
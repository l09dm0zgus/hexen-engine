cmake_minimum_required(VERSION 3.20)
project(Client)


target_sources(${GAME_NAME} PRIVATE
        Application.rc
        main.cpp
        application/Application.cpp
        application/Application.hpp
)

if(MSVC)
    target_compile_options(${GAME_NAME} PRIVATE /W4)
else()
    target_compile_options(${GAME_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(${BUILD_FOR_ANDROID})
    target_link_libraries(${GAME_NAME} nlohmann_json::nlohmann_json SDL3_image::SDL3_image SDL3::SDL3 GLESv3 glm::glm  ${ENGINE_NAME})
else ()
    target_link_libraries(${GAME_NAME} nlohmann_json::nlohmann_json SDL3_image::SDL3_image SDL3::SDL3 libglew_static glm::glm  ${ENGINE_NAME})
endif (${BUILD_FOR_ANDROID})


target_include_directories(${GAME_NAME} PRIVATE ${PARENT_DIR}/engine/src)
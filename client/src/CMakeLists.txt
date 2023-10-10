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

target_link_libraries(${GAME_NAME} PRIVATE ${CORE_MODULE_NAME} ${RENDER_MODULE_NAME} ${COMPONENTS_MODULE_NAME} ${SYSTEMS_MODULE_NAME} ${ENTITY_MODULE_NAME} ${GUI_MODULE_NAME})


target_include_directories(${GAME_NAME} PRIVATE ${PARENT_DIR}/engine/src)
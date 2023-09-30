cmake_minimum_required(VERSION 3.20)
project(Hexen)

message(STATUS "Engine Name:" ${ENGINE_NAME})

target_sources(${ENGINE_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/threads/Thread.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/threads/Config.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/threads/Thread.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/threads/Fiber.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/threads/Fiber.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/task/Callbacks.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/task/Task.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/counter/BaseCounter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/counter/BaseCounter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/counter/AtomicCounter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/counter/TaskCounter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/threads/WaitFreeQueue.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/task/TaskScheduler.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/task/TaskScheduler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Threading.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/task/TaskSchedulerSettings.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/task/TaskSchedulerSettings.cpp
        )
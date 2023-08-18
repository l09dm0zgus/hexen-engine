cmake_minimum_required(VERSION 3.6)
project(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/threads/Thread.h
        ${CMAKE_CURRENT_SOURCE_DIR}/threads/Config.h
        ${CMAKE_CURRENT_SOURCE_DIR}/threads/Thread.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/threads/Fiber.h
        ${CMAKE_CURRENT_SOURCE_DIR}/threads/Fiber.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/task/Callbacks.h
        ${CMAKE_CURRENT_SOURCE_DIR}/task/Task.h
        ${CMAKE_CURRENT_SOURCE_DIR}/counter/BaseCounter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/counter/BaseCounter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/counter/AtomicCounter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/counter/TaskCounter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/threads/WaitFreeQueue.h
        ${CMAKE_CURRENT_SOURCE_DIR}/task/TaskScheduler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/task/TaskScheduler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Threading.h
        ${CMAKE_CURRENT_SOURCE_DIR}/task/TaskSchedulerSettings.h
        ${CMAKE_CURRENT_SOURCE_DIR}/task/TaskSchedulerSettings.cpp
        )
cmake_minimum_required(VERSION 3.6)
project(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Thread.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Thread.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BaseCounter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/BaseCounter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Task.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Task.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TaskManager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TaskManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Fiber.h
        ${CMAKE_CURRENT_SOURCE_DIR}/AtomicCounter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Fiber.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Config.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FiberMutex.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TaskCounter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/detail/ThreadLocal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/detail/FunctionTraits.h
        ${CMAKE_CURRENT_SOURCE_DIR}/detail/FunctionChecks.h
        ${CMAKE_CURRENT_SOURCE_DIR}/detail/Callbacks.h
        ${CMAKE_CURRENT_SOURCE_DIR}/detail/Details.h
        ${CMAKE_CURRENT_SOURCE_DIR}/detail/Delegate.h
        ${CMAKE_CURRENT_SOURCE_DIR}/detail/WaitFreeQueue.h
        )
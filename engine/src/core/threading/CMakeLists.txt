cmake_minimum_required(VERSION 3.6)
project(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
        thread/Thread.h
        thread/Config.h
        thread/Thread.cpp
        thread/Fiber.h
        thread/Fiber.cpp
        task/Callbacks.h
        task/Task.h
        counter/BaseCounter.h
        counter/BaseCounter.cpp
        counter/AtomicCounter.h
        counter/TaskCounter.h
        thread/WaitFreeQueue.h
        task/TaskScheduler.h
        task/TaskScheduler.cpp
        )
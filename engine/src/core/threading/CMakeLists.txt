cmake_minimum_required(VERSION 3.20)
project(Hexen)

target_sources(${CORE_MODULE_NAME} PRIVATE
        threads/Thread.hpp
        threads/Config.hpp
        threads/Thread.cpp
        threads/Fiber.hpp
        threads/Fiber.cpp
        task/Callbacks.hpp
        task/Task.hpp
        counter/BaseCounter.hpp
        counter/BaseCounter.cpp
        counter/AtomicCounter.hpp
        counter/TaskCounter.hpp
        threads/WaitFreeQueue.hpp
        task/TaskScheduler.hpp
        task/TaskScheduler.cpp
        Threading.hpp
        task/TaskSchedulerSettings.hpp
        task/TaskSchedulerSettings.cpp
        )
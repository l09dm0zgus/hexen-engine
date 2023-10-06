cmake_minimum_required(VERSION 3.20)
project(Hexen)

target_sources(${RENDER_ENGINE_NAME} PUBLIC
        GLElementsBuffer.hpp
        GLElementsBuffer.cpp)
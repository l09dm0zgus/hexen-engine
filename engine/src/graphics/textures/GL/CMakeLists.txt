cmake_minimum_required(VERSION 3.20)
project(Hexen)

target_sources(${RENDER_MODULE_NAME} PUBLIC
        GLTexture2D.hpp
        GLTexture2D.cpp
        GLTextureArray.hpp
        GLTextureArray.cpp)
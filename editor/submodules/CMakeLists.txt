cmake_minimum_required(VERSION 3.20)
project(${EDITOR_NAME})

set(CMAKE_CXX_STANDARD 17)

target_sources(${EDITOR_NAME} PRIVATE imgui/imconfig.h
        imgui/imgui.h
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_internal.h
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imstb_rectpack.h
        imgui/imstb_textedit.h
        imgui/imstb_truetype.h
        imgui/misc/single_file/imgui_single_file.h
        imgui/backends/imgui_impl_opengl3.h
        imgui/backends/imgui_impl_opengl3_loader.h
        imgui/backends/imgui_impl_opengl3.cpp
        imgui/backends/imgui_impl_sdl3.h
        imgui/backends/imgui_impl_sdl3.cpp
        imgui/imgui_demo.cpp
        imgui/misc/cpp/imgui_stdlib.h
        imgui/misc/cpp/imgui_stdlib.cpp
        #imgui/backends/imgui_impl_vulkan.h
        #imgui/backends/imgui_impl_vulkan.cpp
        )

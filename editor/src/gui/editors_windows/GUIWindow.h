//
// Created by cx9ps3 on 09.06.2023.
//

#pragma once

#include <string>
#include <imgui.h>
#include <core/memory_pool/AllocatedObject.h>
#include <glm/vec2.hpp>

namespace edit::gui
{
    class GUIWindow : public core::mem::AllocatedObject
    {
    public:
        std::string getName() const noexcept;

        template<class T> void setSize(T &&newSize)
        {
            size = std::forward<T>(newSize);
            setWindowSize();
        }

        glm::vec2 getSize() const noexcept;

        virtual void draw() = 0;
        virtual void begin() = 0;
        virtual void end() = 0;
        virtual ~GUIWindow() = default;
        explicit GUIWindow(std::string name);
        GUIWindow(GUIWindow &&guiWindow) = delete;
        GUIWindow(const GUIWindow &guiWindow) = delete;
        GUIWindow& operator=(GUIWindow &&guiWindow) = delete;
        GUIWindow& operator=(const GUIWindow &guiWindow) = delete;
    protected:
    private:
        void setWindowSize();
        std::string name;
        glm::vec2 size{200,200};
    };
}

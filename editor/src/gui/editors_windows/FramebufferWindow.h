//
// Created by cx9ps3 on 13.07.2023.
//

#ifndef HEXENEDITOR_FRAMEBUFFERWINDOW_H
#define HEXENEDITOR_FRAMEBUFFERWINDOW_H

#include <core/Types.h>
#include <core/graphics/FrameBufferObject.h>
#include <core/graphics/texture/FrameBufferTexture.h>
#include "GUIWindow.h"

namespace edit::gui
{
    class FramebufferWindow : public GUIWindow
    {
    public:
        explicit FramebufferWindow(const std::string &name);
        void begin() override;
        void draw() override;
        void end() override;
    private:
        void clear();
        core::rend::FrameBufferObject frameBufferObject;
        std::unique_ptr<core::rend::FrameBufferTexture> frameBufferTexture;
    protected:
        virtual void render();
    };
}

#endif //HEXENEDITOR_FRAMEBUFFERWINDOW_H

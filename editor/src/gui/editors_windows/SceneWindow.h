//
// Created by cx9ps3 on 09.06.2023.
//

#ifndef HEXENEDITOR_SCENEWINDOW_H
#define HEXENEDITOR_SCENEWINDOW_H

#include <core/Types.h>
#include <core/graphics/FrameBufferObject.h>
#include <core/graphics/texture/FrameBufferTexture.h>
#include "../GUIWindow.h"

namespace edit::gui
{
    class SceneWindow : public GUIWindow
    {
    public:
        SceneWindow(const std::string &name);
        void begin() override;
        void draw() override;
        void end() override;
    private:
        void clear();
        void drawScene();
        core::rend::FrameBufferObject frameBufferObject;
        std::unique_ptr<core::rend::FrameBufferTexture> frameBufferTexture;
    };

}




#endif //HEXENEDITOR_SCENEWINDOW_H

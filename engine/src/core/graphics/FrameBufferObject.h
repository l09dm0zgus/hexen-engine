//
// Created by cx9ps3 on 09.06.2023.
//

#ifndef HEXENEDITOR_FRAMEBUFFEROBJECT_H
#define HEXENEDITOR_FRAMEBUFFEROBJECT_H

#include <glm/vec2.hpp>
#include "../Types.h"
#include "RenderBufferObject.h"

namespace core::rend
{
    class FrameBufferObject
    {
    public:
        FrameBufferObject();
        ~FrameBufferObject();
        void bind();
        void unbind();
        void setSize(const glm::vec2 &size);
    private:
        u32 object{0};
        RenderBufferObject renderBufferObject;
    };
}

#endif //HEXENEDITOR_FRAMEBUFFEROBJECT_H

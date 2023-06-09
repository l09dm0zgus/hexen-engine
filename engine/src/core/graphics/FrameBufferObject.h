//
// Created by cx9ps3 on 09.06.2023.
//

#ifndef HEXENEDITOR_FRAMEBUFFEROBJECT_H
#define HEXENEDITOR_FRAMEBUFFEROBJECT_H

#include "../Types.h"

namespace core::rend
{
    class FrameBufferObject
    {
    public:
        FrameBufferObject();
        ~FrameBufferObject();
        void bind();
        void unbind();
    private:
        u32 object{};
    };
}

#endif //HEXENEDITOR_FRAMEBUFFEROBJECT_H

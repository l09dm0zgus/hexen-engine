//
// Created by cx9ps3 on 09.06.2023.
//

#ifndef HEXENEDITOR_RENDERBUFFEROBJECT_H
#define HEXENEDITOR_RENDERBUFFEROBJECT_H
#include "../Types.h"

namespace core::rend
{
    class RenderBufferObject
    {
    private:
        u32 object{0};
    public:
        u32 getID() const noexcept;
        RenderBufferObject();
        ~RenderBufferObject();
        void bind();
        void unbind();
    };
}



#endif //HEXENEDITOR_RENDERBUFFEROBJECT_H

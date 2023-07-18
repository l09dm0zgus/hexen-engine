//
// Created by cx9ps3 on 09.06.2023.
//

#pragma once

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
        void bind() const;
        void unbind();
    };
}

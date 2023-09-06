//
// Created by cx9ps3 on 04.01.23.
//

#pragma once

#include "../Types.h"
namespace hexen::engine::graphics::gl
{
    class VertexArrayObject
    {
    public:
        VertexArrayObject();
        ~VertexArrayObject();
        void bind() const;
        void unbind();
    private:
        core::u32 object{0};
    };

}

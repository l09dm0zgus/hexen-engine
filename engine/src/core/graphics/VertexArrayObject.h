//
// Created by cx9ps3 on 04.01.23.
//

#pragma once

#include "../Types.h"
namespace core::rend
{
    class VertexArrayObject
    {
    public:
        VertexArrayObject();
        ~VertexArrayObject();
        void bind() const;
        void unbind();
    private:
        u32 object{0};
    };

}

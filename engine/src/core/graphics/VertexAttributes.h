//
// Created by cx9ps3 on 03.01.23.
//

#pragma once

#include <cstddef>
#include "../Types.h"
namespace core::rend
{
    class VertexAttributes
    {
    public:
        void add(i32 size,i32 stride,i32 offset);
        void add(i32 size,size_t typeSize,i32 offset);
        void vertexDivisor(i32 index,i32 divisor);
    private:
        i32 attributes{0};
    };

}

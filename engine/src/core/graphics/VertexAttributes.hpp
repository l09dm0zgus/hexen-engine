//
// Created by cx9ps3 on 03.01.23.
//

#pragma once

#include <cstddef>
#include "../Types.hpp"
namespace hexen::engine::graphics::gl
{
    class VertexAttributes
    {
    public:
        void add(core::i32 size,core::i32 stride,core::i32 offset);
        void add(core::i32 size,size_t typeSize,core::i32 offset);
        void vertexDivisor(core::i32 index,core::i32 divisor);
    private:
        core::i32 attributes{0};
    };

}

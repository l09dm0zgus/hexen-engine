//
// Created by cx9ps3 on 02.01.23.
//

#pragma once


#include <cstddef>
#include "RectangleData.h"
#include "../Types.h"
namespace core::rend
{
    class VertexBufferObject
    {
    public:
        VertexBufferObject();
        ~VertexBufferObject();
        void bind(const RectangleData &rectangleData) const;
        void bind(size_t size,vptr data) const;
        void unbind();
    private:
        u32 object{0};
    };
}

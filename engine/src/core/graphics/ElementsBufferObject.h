//
// Created by cx9ps3 on 14.05.2023.
//
#pragma once

#include "RectangleData.h"
#include "../Types.h"

namespace core::rend
{
    class ElementsBufferObject
    {
    public:
        ElementsBufferObject();
        ~ElementsBufferObject();
        void bind(const RectangleData &rectangleData) const;
        void unbind();
    private:
        u32 object{0};
    };
}

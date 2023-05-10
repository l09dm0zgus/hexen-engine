//
// Created by cx9ps3 on 02.01.23.
//

#ifndef BATTLEBLAZE_VERTEXBUFFEROBJECT_H
#define BATTLEBLAZE_VERTEXBUFFEROBJECT_H

#include <cstddef>
#include "RectangleVertices.h"
#include "../Types.h"
namespace core::rend
{
    class VertexBufferObject
    {
    public:
        VertexBufferObject();
        ~VertexBufferObject();
        void bind(RectangleVertices &vertices);
        void bind(size_t size,vptr data);
        void unbind();
    private:
        u32 object{0};
    };
}

#endif //BATTLEBLAZE_VERTEXBUFFEROBJECT_H

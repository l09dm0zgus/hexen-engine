//
// Created by cx9ps3 on 02.01.23.
//

#ifndef BATTLEBLAZE_VERTEXBUFFEROBJECT_H
#define BATTLEBLAZE_VERTEXBUFFEROBJECT_H

#include <cstddef>
#include "RectangleVertices.h"
namespace core::rend
{
    class VertexBufferObject
    {
    public:
        VertexBufferObject();
        ~VertexBufferObject();
        void bind(RectangleVertices &vertices);
        void bind(size_t size,void* data);
        void unbind();
    private:
        unsigned int object{0};
    };
}

#endif //BATTLEBLAZE_VERTEXBUFFEROBJECT_H

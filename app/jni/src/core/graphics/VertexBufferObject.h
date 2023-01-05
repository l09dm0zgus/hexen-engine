//
// Created by cx9ps3 on 02.01.23.
//

#ifndef BATTLEBLAZE_VERTEXBUFFEROBJECT_H
#define BATTLEBLAZE_VERTEXBUFFEROBJECT_H
#include "RectangleVertices.h"

class VertexBufferObject
{
public:
    VertexBufferObject();
    ~VertexBufferObject();
    void bind(RectangleVertices &vertices);
    void unbind();
private:
    unsigned int object{0};
};


#endif //BATTLEBLAZE_VERTEXBUFFEROBJECT_H

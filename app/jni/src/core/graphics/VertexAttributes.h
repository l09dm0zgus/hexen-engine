//
// Created by cx9ps3 on 03.01.23.
//

#ifndef BATTLEBLAZE_VERTEXATTRIBUTES_H
#define BATTLEBLAZE_VERTEXATTRIBUTES_H
#include <cstddef>
namespace core::rend
{
    class VertexAttributes
    {
    public:
        void add(int size,int stride,int offset);
        void add(int size,size_t typeSize,int offset);
        void vertexDivisor(int index,int divisor);
    private:
        int attributes{0};
    };

}

#endif //BATTLEBLAZE_VERTEXATTRIBUTES_H

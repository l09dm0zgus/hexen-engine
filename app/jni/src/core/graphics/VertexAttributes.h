//
// Created by cx9ps3 on 03.01.23.
//

#ifndef BATTLEBLAZE_VERTEXATTRIBUTES_H
#define BATTLEBLAZE_VERTEXATTRIBUTES_H


class VertexAttributes
{
public:
    void add(int size,int stride,int offset);
private:
    int attributes{0};
};


#endif //BATTLEBLAZE_VERTEXATTRIBUTES_H

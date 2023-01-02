//
// Created by cx9ps3 on 02.01.23.
//

#ifndef BATTLEBLAZE_RECTANGLEVERTICES_H
#define BATTLEBLAZE_RECTANGLEVERTICES_H


class RectangleVertices
{
public:
    float *data();

private:
    float vertices[18]
    {
        -0.5f,-5.0f,0.0f,
        -0.5f,0.5f,0.0f,
        0.5f,0.5f,0.5f,
        0.5f,0.5f,0.5f,
        0.5f,-0.5f,0.5f,
        -0.5f,-5.0f,0.0f,

    };
};


#endif //BATTLEBLAZE_RECTANGLEVERTICES_H

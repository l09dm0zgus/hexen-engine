//
// Created by cx9ps3 on 02.01.23.
//

#ifndef BATTLEBLAZE_RECTANGLEDATA_H
#define BATTLEBLAZE_RECTANGLEDATA_H

namespace core::rend
{
    enum RectangleDataSizes
    {
        VERTICES_ARRAY_SIZE = 12,
        INDICES_ARRAY_SIZE = 6
    };
    struct RectangleData
    {
        const float vertices[RectangleDataSizes::VERTICES_ARRAY_SIZE] =
                {
                        -1.0f, -1.0f, -0.0f,
                        1.0f,  1.0f, -0.0f,
                        -1.0f,  1.0f, -0.0f,
                        1.0f, -1.0f, -0.0f
                };
        const unsigned int indices[RectangleDataSizes::INDICES_ARRAY_SIZE] =
                {
                        0, 1, 2,
                        0, 3, 1
                };
    };
}

#endif //BATTLEBLAZE_RECTANGLEDATA_H

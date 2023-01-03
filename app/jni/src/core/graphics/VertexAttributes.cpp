//
// Created by cx9ps3 on 03.01.23.
//

#include "VertexAttributes.h"
#include <GLES3/gl31.h>

void VertexAttributes::add(int size, int offset)
{
    glVertexAttribPointer(attributes, size, GL_FLOAT, GL_FALSE, size * sizeof(float), (void*)offset);
    glEnableVertexAttribArray(attributes);
    attributes++;
}

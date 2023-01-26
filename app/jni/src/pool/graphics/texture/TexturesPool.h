//
// Created by cx9ps3 on 26.01.23.
//

#ifndef BATTLEBLAZE_TEXTURESPOOL_H
#define BATTLEBLAZE_TEXTURESPOOL_H

#include "../../../core/graphics/texture/Texture.h"
#include "../../Pool.h"

class TexturesPool
{
public:
    TexturesPool(int numberOfObjects);
    ~TexturesPool();
    Texture* create(const std::string pathToImage,int wrapMode = GL_REPEAT ,int filterMode = GL_NEAREST);
    void remove();
private:
    Pool<Texture> *pool{nullptr};
};


#endif //BATTLEBLAZE_TEXTURESPOOL_H

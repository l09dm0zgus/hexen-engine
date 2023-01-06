//
// Created by cx9ps3 on 06.01.23.
//

#ifndef BATTLEBLAZE_TEXTURE_H
#define BATTLEBLAZE_TEXTURE_H
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <GLES3/gl31.h>
class Texture
{
public:
    Texture(const std::string pathToImage,int wrapMode = GL_REPEAT ,int filterMode = GL_NEAREST);
    void bind(int id);
    ~Texture();
private:
    SDL_Surface *surface{nullptr};
    unsigned int  textureId;
    void setTextureParameters(int wrapMode ,int filterMode);

};


#endif //BATTLEBLAZE_TEXTURE_H

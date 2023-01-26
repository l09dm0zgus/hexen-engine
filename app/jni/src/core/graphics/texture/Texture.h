//
// Created by cx9ps3 on 06.01.23.
//

#ifndef BATTLEBLAZE_TEXTURE_H
#define BATTLEBLAZE_TEXTURE_H
#ifndef  __ANDROID__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <GLES3/gl31.h>
#endif

#include <string>

class Texture
{
public:
    void create(const std::string pathToImage,int wrapMode = GL_REPEAT ,int filterMode = GL_NEAREST);
    void bind(int id);
    ~Texture();
private:
    SDL_Surface *surface{nullptr};
    unsigned int  textureId;
    void setTextureParameters(int wrapMode ,int filterMode);

};


#endif //BATTLEBLAZE_TEXTURE_H

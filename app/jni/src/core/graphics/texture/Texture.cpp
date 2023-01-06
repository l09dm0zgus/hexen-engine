//
// Created by cx9ps3 on 06.01.23.
//

#include "Texture.h"
#include <GLES3/gl31.h>

Texture::Texture(const std::string pathToImage,int wrapMode  ,int filterMode)
{
    surface = IMG_Load(pathToImage.c_str());
    if(surface == nullptr)
    {
        SDL_Log("Error : Failed to load %s image.",pathToImage.c_str());
    }

    int mode = GL_RGB;
    if(surface->format->BitsPerPixel == 4)
    {
        mode = GL_RGBA;
    }
    glGenTextures(1,&textureId);
    glBindTexture(GL_TEXTURE_2D,textureId);
    setTextureParameters(wrapMode,filterMode);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

}

void Texture::setTextureParameters(int wrapMode, int filterMode)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);

}

Texture::~Texture()
{
    SDL_FreeSurface(surface);
}

void Texture::bind(int id)
{
    glActiveTexture(GL_TEXTURE0+id);
    glBindTexture(GL_TEXTURE_2D,textureId);
}

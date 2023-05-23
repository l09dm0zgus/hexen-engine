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
#include <SDL3/SDL.h>
#include <SDL_image.h>
#include <GLES3/gl31.h>
#endif

#include <string>
#include "../../memory_pool/AllocatedObject.h"
namespace core::rend
{
    class Texture : public mem::AllocatedObject
    {
    public:
        Texture(const std::string &pathToImage,int wrapMode = GL_REPEAT ,int filterMode = GL_NEAREST);
        void bind(u32 id) const;
        ~Texture();
    private:
        SDL_Surface *surface{nullptr};
        u32 textureId;
        void setTextureParameters(int wrapMode ,int filterMode);

    };
}

#endif //BATTLEBLAZE_TEXTURE_H

//
// Created by cx9ps3 on 06.01.23.
//

#ifndef BATTLEBLAZE_TEXTURE_H
#define BATTLEBLAZE_TEXTURE_H

#include <SDL3/SDL.h>
#include <SDL_image.h>
#ifndef  __ANDROID__
#include <GL/glew.h>
#else
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
        ~Texture() override;
        Texture(const Texture &texture) = default;
        Texture(Texture &&texture) = default;
        Texture& operator=(const Texture &texture) = default;
        Texture& operator=(Texture &&texture) = default;
    private:
        SDL_Surface *surface{nullptr};
        u32 textureId;
        void setTextureParameters(int wrapMode ,int filterMode);

    };
}

#endif //BATTLEBLAZE_TEXTURE_H

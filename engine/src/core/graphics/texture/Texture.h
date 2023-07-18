//
// Created by cx9ps3 on 06.01.23.
//

#pragma once


#include <SDL3/SDL.h>
#include <SDL_image.h>
#include <string>
#include "../../memory_pool/AllocatedObject.h"
namespace core::rend
{
    class Texture : public mem::AllocatedObject
    {
    public:
        explicit Texture(const std::string &pathToImage,int wrapMode = 0x2901 ,int filterMode = 0x2600);
        void bind(u32 id) const;
        u32 getId() const noexcept;
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


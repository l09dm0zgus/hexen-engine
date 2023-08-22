//
// Created by cx9ps3 on 09.06.2023.
//

#pragma once

#include <glm/vec2.hpp>
#include "../../memory_pool/AllocatedObject.h"

namespace core::rend
{
    class FrameBufferTexture : public mem::AllocatedObject
    {
    private:
        u32 object{0};
    public:

        /**
        * @class FrameBufferTexture
        * @brief Represents a texture used as a frame buffer object attachment.
        *
        * The FrameBufferTexture class is responsible for creating and managing a texture that can be
        * attached to a frame buffer object (FBO). The texture is used as a rendering destination when
        * performing off-screen rendering.
        *
        * This class provides a constructor to create a FrameBufferTexture object with a specified size.
        */

        explicit FrameBufferTexture(const glm::vec2 &size);

        /**
        * @class FrameBufferTexture
        * @brief Represents a texture attached to a frame buffer object.
        *
        * This class is responsible for handling the destruction of frame buffer textures.
        * It provides a destructor to release any associated resources.
        */


        ~FrameBufferTexture() override;

        /**
        * @brief Retrieves the ID of the frame buffer texture.
        *
        * This function returns the ID of the frame buffer texture.
        *
        * @return The ID of the frame buffer texture.
        */

        u32 getID() const noexcept;

        /**
        * @brief Unbinds the FrameBufferTexture object.
        *
        * This function unbinds the FrameBufferTexture object, meaning that it is no longer the active
        * frame buffer target for rendering operations. After calling this function, rendering operations
        * will target the default frame buffer.
        *
        * @see core::rend::FrameBufferTexture::bind()
        */


        void unbind();

        /**
        * Resizes the framebuffer texture to the given size.
        *
        * @param size The new size of the framebuffer texture.
        */

        void resize(const glm::vec2 &size) const;
    };
}


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
        explicit FrameBufferTexture(const glm::vec2 &size);
        ~FrameBufferTexture() override;
        u32 getID() const noexcept;
        void unbind();
        void resize(const glm::vec2 &size) const;
    };
}


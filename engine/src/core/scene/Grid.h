//
// Created by cx9ps3 on 29.07.2023.
//
#pragma once

#include <glm/vec2.hpp>
#include "../memory_pool/AllocatedObject.h"
namespace core
{
    class Grid : public mem::AllocatedObject
    {
    private:
        glm::vec2 unitSize{0};
        float numberOfCells{0};
        glm::vec2 size;
    public:
        Grid();
        glm::vec2  getUnitSize() const noexcept;
        float getNumberOfCells() const noexcept;
        glm::vec2 getSize() const noexcept;
    };
}


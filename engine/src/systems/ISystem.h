//
// Created by cx9ps3 on 13.07.2023.
//

#pragma once


#include "../core/memory_pool/MemoryPool.h"

namespace sys
{
    class ISystem : public core::mem::AllocatedObject
    {
    public:
        ISystem() = default;
        virtual ~ISystem() = default;
        ISystem(ISystem &&system) = delete;
        ISystem(const ISystem& system) = delete;
        ISystem& operator=(ISystem &&system) = delete;
        ISystem& operator=(const ISystem &system) = delete;
        virtual void start() = 0;
        virtual void update(float deltaTime) = 0;

    };
}

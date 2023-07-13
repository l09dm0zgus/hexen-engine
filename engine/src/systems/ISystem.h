//
// Created by cx9ps3 on 13.07.2023.
//

#ifndef HEXENEDITOR_ISYSTEM_H
#define HEXENEDITOR_ISYSTEM_H
#include "core/memory_pool/AllocatedObject.h"

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

#endif //HEXENEDITOR_ISYSTEM_H

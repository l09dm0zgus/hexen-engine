//
// Created by cx9ps3 on 13.07.2023.
//

#ifndef HEXENEDITOR_DEBUGRENDERSYSTEM_H
#define HEXENEDITOR_DEBUGRENDERSYSTEM_H

#include <core/Types.h>

namespace sys
{
    class DebugRenderSystem
    {
        explicit DebugRenderSystem(core::u32 sizeOfVectors);
        void start();
        void update(float deltaTime);
    private:
        //void updateSpriteModelMatrix(comp::rend::SpriteComponent &spriteComponent);
        //void updateViewAndProjectionMatrices(comp::rend::SpriteComponent *spriteComponent);
    };
}



#endif //HEXENEDITOR_DEBUGRENDERSYSTEM_H

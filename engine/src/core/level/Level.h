//
// Created by cx9ps3 on 24.05.2023.
//

#ifndef HEXENREICH_LEVEL_H
#define HEXENREICH_LEVEL_H

#include "../../entity/scene/SceneEntity.h"

namespace core
{
    struct Level
    {
        glm::vec2 levelSize;
        std::shared_ptr<ent::SceneEntity> levelRoot;
    };
}



#endif //HEXENREICH_LEVEL_H

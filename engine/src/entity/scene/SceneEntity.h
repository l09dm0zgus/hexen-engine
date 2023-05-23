//
// Created by cx9ps3 on 19.05.2023.
//

#ifndef BATTLEBLAZE_SCENEENTITY_H
#define BATTLEBLAZE_SCENEENTITY_H
#include "../Entity.h"
#include "../../core/Types.h"
#include "../../components/transform/TransformComponent.h"

namespace ent
{
    class SceneEntity : public Entity
    {
    public:
        SceneEntity(std::string name);
        SceneEntity(std::string name, const std::string &UUID);
        SceneEntity* getParent() const noexcept;
        void setParent(SceneEntity *newParent);
        std::shared_ptr<comp::TransformComponent> transformComponent;
        template<class T> void addChild(T &&name);
        void forceUpdateTransformMatrix();
        void updateTransformMatrix();
    private:
        std::string name;
        core::HashTable<std::string,std::unique_ptr<SceneEntity>> childrens;
        SceneEntity *parent{nullptr};
    };
}

#endif //BATTLEBLAZE_SCENEENTITY_H

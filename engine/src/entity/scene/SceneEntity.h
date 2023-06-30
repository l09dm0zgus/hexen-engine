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
        ~SceneEntity() override;
        std::string getName() const noexcept;
        SceneEntity* getParent() const noexcept;
        void setParent(SceneEntity *newParent);
        std::shared_ptr<comp::TransformComponent> transformComponent;
        bool hasChildrens() const noexcept;
        core::HashTable<std::string,std::shared_ptr<SceneEntity>> getChildrens() const noexcept;
        std::shared_ptr<SceneEntity> getChild(const std::string &name) const noexcept;
        std::shared_ptr<SceneEntity> getChildByUUID(const std::string &UUID) const noexcept;
        core::HashTable<std::string,std::shared_ptr<SceneEntity>>::Iterator findChild(const std::string &UUID);

        template<class T, class... Ts> void addChild(Ts&&... params)
        {
            childrens.set(generateUUIDV4(),core::mem::make_shared<T>(params...));
        }

        template<class T> void addChild(T &&entityName)
        {
            std::string childUUID = generateUUIDV4();
            auto child = core::mem::make_shared<SceneEntity>(entityName,childUUID);
            childrens.set(childUUID,child);
            childrens[childUUID]->setParent(this);
        }

        void addChildByPointer(const std::shared_ptr<SceneEntity> &sceneEntity);

        void forceUpdateTransformMatrix();
        void updateTransformMatrix();
        void detachFromParent();
        void removeChild(const std::string &name);
        void removeChildByUUID(const std::string &UUID);
    private:
        std::string name;
        core::HashTable<std::string,std::shared_ptr<SceneEntity>> childrens;
        SceneEntity *parent{nullptr};
        core::HashTable<std::string, std::shared_ptr<ent::SceneEntity>>::ConstIterator find(const std::string &name) const;
    };
}

#endif //BATTLEBLAZE_SCENEENTITY_H

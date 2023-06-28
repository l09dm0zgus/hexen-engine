//
// Created by cx9ps3 on 19.05.2023.
//

#include "SceneEntity.h"

ent::SceneEntity::SceneEntity(std::string name) : ent::Entity() , name(std::move(name))
{
    //TODO add getting TransformComponent from system
    transformComponent = core::mem::make_shared<comp::TransformComponent>();
}

ent::SceneEntity::SceneEntity(std::string name, const std::string &UUID) : ent::Entity(name) , name(std::move(name))
{
//TODO add getting TransformComponent from system
    transformComponent = core::mem::make_shared<comp::TransformComponent>();
}

ent::SceneEntity *ent::SceneEntity::getParent() const noexcept
{
    return parent;
}

void ent::SceneEntity::setParent(ent::SceneEntity *newParent)
{
    parent = newParent;
}

void ent::SceneEntity::forceUpdateTransformMatrix()
{
    if(parent != nullptr)
    {
        transformComponent->updateTransformMatrix(parent->transformComponent->getTransformMatrix());
    }
    else
    {
        transformComponent->updateTransformMatrix();
    }

}

void ent::SceneEntity::updateTransformMatrix()
{
    if (transformComponent->isDirty())
    {
        forceUpdateTransformMatrix();
        return;
    }

    for (auto&& child : childrens)
    {
        child.value->updateTransformMatrix();
    }
}

void ent::SceneEntity::detachFromParent()
{
    if(parent != nullptr)
    {
        parent->removeChild(name);
        parent = nullptr;
    }
}

void ent::SceneEntity::removeChild(const std::string &name)
{
    auto  it = findChild(name);

    if(it != childrens.end())
    {
        childrens.remove(it->key);
    }
}

std::string ent::SceneEntity::getName() const noexcept
{
    return name;
}

void ent::SceneEntity::removeChildByUUID(const std::string &UUID)
{
    childrens.remove(UUID);
}

bool ent::SceneEntity::hasChildrens() const noexcept
{
    return childrens.empty();
}


core::HashTable<std::string, std::shared_ptr<ent::SceneEntity>> ent::SceneEntity::getChildrens() const noexcept
{
    return childrens;
}

std::shared_ptr<ent::SceneEntity> ent::SceneEntity::getChild(const std::string &name) const noexcept
{
    auto  it = findChild(name);

    if(it == childrens.end())
    {
        return nullptr;
    }

    return it->value;
}

std::shared_ptr<ent::SceneEntity> ent::SceneEntity::getChildByUUID(const std::string &UUID) const noexcept
{
    return childrens.getCopy(UUID);
}

core::HashTable<std::string, std::shared_ptr<ent::SceneEntity>>::Iterator ent::SceneEntity::findChild(const std::string &name) const
{
    return std::find_if(childrens.begin(),childrens.end(),[&name](const auto& keyValue){
        return name == keyValue.value->getName();
    });;
}



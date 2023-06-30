//
// Created by cx9ps3 on 19.05.2023.
//

#include "SceneEntity.h"
#include <algorithm>

ent::SceneEntity::SceneEntity(std::string name) : ent::Entity() , name(std::move(name))
{
    //TODO add getting TransformComponent from system
    transformComponent = core::mem::make_shared<comp::TransformComponent>();
}

ent::SceneEntity::SceneEntity(std::string name, const std::string &UUID) : ent::Entity(UUID) , name(std::move(name))
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
    if(hasChildrens())
    {
        auto  it = find(name);

        if(it != childrens.cend())
        {
            childrens.remove(it->key);
        }
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
    return !childrens.empty();
}


core::HashTable<std::string, std::shared_ptr<ent::SceneEntity>> ent::SceneEntity::getChildrens() const noexcept
{
    return childrens;
}

std::shared_ptr<ent::SceneEntity> ent::SceneEntity::getChild(const std::string &name) const noexcept
{
    auto  it = find(name);

    if(it == childrens.cend())
    {
        return nullptr;
    }

    return it->value;
}

std::shared_ptr<ent::SceneEntity> ent::SceneEntity::getChildByUUID(const std::string &UUID) const noexcept
{
    return *childrens.get(UUID);
}

core::HashTable<std::string, std::shared_ptr<ent::SceneEntity>>::ConstIterator ent::SceneEntity::find(const std::string &name) const
{
    auto it = std::find_if(childrens.cbegin(),childrens.cend(),[&name](const auto& keyValue){
        return name == keyValue.value->getName();
    });
    return it;
}

void ent::SceneEntity::addChildByPointer(const std::shared_ptr<SceneEntity> &sceneEntity)
{
    std::cout << "Adding child with name: " << sceneEntity->getName() << " UUID: " << sceneEntity->getUUID() << "\n";
    childrens.set(sceneEntity->getUUID(),sceneEntity);
}

core::HashTable<std::string, std::shared_ptr<ent::SceneEntity>>::Iterator ent::SceneEntity::findChild(const std::string &UUID)
{
    auto it = childrens.find(UUID);
    if(it != childrens.end())
    {
        return it;
    }
    else
    {
        for (const auto& child : childrens)
        {
            it = child.value->findChild(UUID);
            if(it != child.value->getChildrens().end())
            {
                return it;
            }
        }
    }
    return childrens.end();
}

ent::SceneEntity::~SceneEntity()
{
    std::cout << "Entity with name: " << name << " UUID: " << getUUID() << " destroyed\n";
}



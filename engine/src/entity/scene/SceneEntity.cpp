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

ent::SceneEntity* ent::SceneEntity::getParent() const noexcept
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
    auto child = childrens.get(UUID);
    if(child != nullptr)
    {
        return *child;
    }
    else
    {
        return nullptr;
    }
}

core::HashTable<std::string, std::shared_ptr<ent::SceneEntity>>::ConstIterator ent::SceneEntity::find(const std::string &name) const
{
    auto it = std::find_if(childrens.cbegin(),childrens.cend(),[&name](const auto& keyValue){
        return name == keyValue.value->getName();
    });
    return it;
}

void ent::SceneEntity::changeParent(std::shared_ptr<SceneEntity> &newParent)
{
    if(newParent != nullptr && newParent.get() != parent && newParent.get() != this)
    {
        if(parent != nullptr)
        {
            auto  child = parent->getChildByUUID(getUUID());
            if (child != nullptr)
            {
                newParent->addChildByPointer(child);
                parent->removeChildByUUID(getUUID());
            }
        }
        else
        {
            newParent->addChildByPointer(std::shared_ptr<SceneEntity>(this));
        }
    }

    parent = newParent.get();

}

void ent::SceneEntity::addChildByPointer(const std::shared_ptr<SceneEntity> &newChild)
{
    childrens.set(newChild->getUUID(),newChild);
}

bool ent::SceneEntity::isNodeExist(const std::shared_ptr<ent::SceneEntity> &node,const std::string &UUID)
{
    if(node->getUUID() == UUID)
    {
        return true;
    }
    else
    {
        for (const auto& child : node->childrens)
        {
           if(SceneEntity::isNodeExist(child.value,UUID))
           {
                return true;
           }
        }
    }
    return false;
}

std::shared_ptr<ent::SceneEntity> ent::SceneEntity::getNode(const std::shared_ptr<ent::SceneEntity> &node,const std::string &UUID)
{
    if(node->getUUID() == UUID)
    {
        return node;
    }
    else
    {
        for (const auto& child : node->childrens)
        {
            auto result = SceneEntity::getNode(child.value,UUID);
            if(result != nullptr)
            {
                return result;
            }

        }
    }
    return nullptr;
}



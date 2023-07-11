//
// Created by cx9ps3 on 24.05.2023.
//

#include "Scene.h"

core::Scene::Scene(const std::string &name) : name(name) , size(1024.0f) , unitSize(32.0f)
{
    root = mem::make_shared<ent::SceneEntity>(name);

    //temporary , entities will be loaded from file
    root->addChild("Scene_Entity_0");
    root->addChild("Scene_Entity_1");
    root->addChild("Scene_Entity_2");
    root->getChild("Scene_Entity_2")->addChild("Scene_Entity_3");
    root->getChild("Scene_Entity_2")->getChild("Scene_Entity_3")->addChild("Scene_Entity_4");
    root->getChild("Scene_Entity_2")->getChild("Scene_Entity_3")->addChild("Scene_Entity_5");
}

core::Scene::Scene(const std::string &name, const glm::vec2 &size, const glm::vec2 &unitSize) : Scene(name)
{
    this->unitSize = unitSize;
    this->size = size;
}

core::Scene::SceneIterator core::Scene::begin()
{
    return SceneIterator(root);
}

core::Scene::SceneIterator core::Scene::end()
{
    return SceneIterator(nullptr);
}

core::Scene::SceneConstantIterator core::Scene::cbegin() const
{
    return SceneConstantIterator(root);
}

core::Scene::SceneConstantIterator core::Scene::cend() const
{
    return SceneConstantIterator(nullptr);
}

core::Scene::SceneConstantIterator core::Scene::find(const std::string &UUID) const
{
    return core::Scene::SceneConstantIterator(root->getDescendant(UUID));
}

core::Scene::SceneIterator core::Scene::find(const std::string &UUID)
{
    return SceneIterator(root->getDescendant(UUID));
}

void core::Scene::erase(const std::string &UUID)
{
    auto it = find(UUID);
    erase(it);
}

void core::Scene::erase(const core::Scene::SceneIterator &sceneIterator)
{
    if(sceneIterator != end() && sceneIterator->getParent() != nullptr)
    {
        sceneIterator->getParent()->removeChildByUUID(sceneIterator->getUUID());
    }
}

void core::Scene::forEach(std::function<void(std::shared_ptr<ent::SceneEntity> &)> callback)
{
    for(auto entity : *this)
    {
        callback(entity);
    }
}

core::Scene::SceneIterator core::Scene::SceneIterator::operator++(core::i32)
{
    auto tmp = *this;
    ++(*this);
    return tmp;
}

core::Scene::SceneIterator core::Scene::SceneIterator::operator--(core::i32)
{
    auto tmp = *this;
    --(*this);
    return tmp;
}

void core::Scene::SceneIterator::traverseTree(std::shared_ptr<ent::SceneEntity> &node)
{
    if(node->getUUID() != usedNodes.top().first && !usedNodes.top().second)
    {
        usedNodes.emplace(node->getUUID(), true);
        return;
    }
    for(auto& child : node->getChildrens())
    {
        traverseTree(child.value);
    }
}



std::shared_ptr<ent::SceneEntity> core::Scene::SceneIterator::operator->() const
{
    assert(root == nullptr && "cannot dereference end iterator");
    return root->getDescendant(usedNodes.top().first);
}

std::shared_ptr<ent::SceneEntity> core::Scene::SceneIterator::operator*() const
{
    return operator->();
}

bool core::Scene::SceneIterator::operator==(const core::Scene::SceneIterator &sceneIterator) const
{
    return root == sceneIterator.root;
}

bool core::Scene::SceneIterator::operator!=(const core::Scene::SceneIterator &sceneIterator) const
{
    return !operator==(sceneIterator);
}

core::Scene::SceneIterator::SceneIterator(const std::shared_ptr<ent::SceneEntity> &root) : root(root)
{

}

core::Scene::SceneIterator &core::Scene::SceneIterator::operator++()
{
    assert(root == nullptr && "cannot increment end iterator");
    traverseTree(root);
    return *this;
}

core::Scene::SceneIterator &core::Scene::SceneIterator::operator--()
{
    usedNodes.pop();
    return *this;
}

const std::shared_ptr<ent::SceneEntity> core::Scene::SceneConstantIterator::operator->() const
{
    return SceneIterator::operator->();
}

const std::shared_ptr<ent::SceneEntity> core::Scene::SceneConstantIterator::operator*() const
{
    return SceneIterator::operator*();
}

core::Scene::SceneConstantIterator::SceneConstantIterator(const std::shared_ptr<ent::SceneEntity> &root ): SceneIterator(root)
{

}

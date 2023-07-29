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
    return SceneIterator(root,0);
}

core::Scene::SceneIterator core::Scene::end()
{
    return SceneIterator(root);
}

core::Scene::SceneConstantIterator core::Scene::cbegin() const
{
    return SceneConstantIterator(root, 0);
}

core::Scene::SceneConstantIterator core::Scene::cend() const
{
    return SceneConstantIterator(root);
}

core::Scene::SceneConstantIterator core::Scene::find(const std::string &UUID) const
{
    return SceneConstantIterator(ent::SceneEntity::getNode(root,UUID));
}

core::Scene::SceneIterator core::Scene::find(const std::string &UUID)
{
    return SceneIterator(ent::SceneEntity::getNode(root,UUID));
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

std::shared_ptr<ent::SceneEntity> core::Scene::getRootNode() const noexcept
{
    return root;
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

void core::Scene::SceneIterator::traverseTree(const std::shared_ptr<ent::SceneEntity> &node)
{
    auto it = std::find(visitedNode.cbegin(),visitedNode.cend(),node->getUUID());
    if(it == visitedNode.cend())
    {
        visitedNode.push_back(node->getUUID());
    }
    for(auto& child : node->getChildrens())
    {
        traverseTree(child.value);
    }

}



std::shared_ptr<ent::SceneEntity> core::Scene::SceneIterator::operator->() const
{
    assert(index < visitedNode.size() && "cannot dereference end iterator");
    return ent::SceneEntity::getNode(root,visitedNode[index]);
}

std::shared_ptr<ent::SceneEntity> core::Scene::SceneIterator::operator*() const
{
    return operator->();
}

bool core::Scene::SceneIterator::operator==(const core::Scene::SceneIterator &sceneIterator) const
{
    return root == sceneIterator.root && index == sceneIterator.index;
}

bool core::Scene::SceneIterator::operator!=(const core::Scene::SceneIterator &sceneIterator) const
{
    return !operator==(sceneIterator);
}

core::Scene::SceneIterator::SceneIterator(const std::shared_ptr<ent::SceneEntity> &root,u32 index) : root(root) , index(index)
{
    traverseTree(root);
}

core::Scene::SceneIterator &core::Scene::SceneIterator::operator++()
{
    assert(index < visitedNode.size() && "cannot increment end iterator");
    index++;
    return *this;
}

core::Scene::SceneIterator &core::Scene::SceneIterator::operator--()
{
    index--;
    return *this;
}

core::Scene::SceneIterator::SceneIterator(const std::shared_ptr<ent::SceneEntity> &root) : root(root)
{
    traverseTree(root);
    index = visitedNode.size();
}

glm::vec2 core::Scene::getUnitSize() const noexcept
{
    return unitSize;
}

glm::vec2 core::Scene::getSize() const noexcept
{
    return size;
}

const std::shared_ptr<ent::SceneEntity> core::Scene::SceneConstantIterator::operator->() const
{
    return SceneIterator::operator->();
}

const std::shared_ptr<ent::SceneEntity> core::Scene::SceneConstantIterator::operator*() const
{
    return SceneIterator::operator*();
}

core::Scene::SceneConstantIterator::SceneConstantIterator(const std::shared_ptr<ent::SceneEntity> &root,u32 index ): SceneIterator(root,index)
{

}

core::Scene::SceneConstantIterator::SceneConstantIterator(const std::shared_ptr<ent::SceneEntity> &root) : SceneIterator(root)
{

}

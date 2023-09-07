//
// Created by cx9ps3 on 24.05.2023.
//

#include "Scene.hpp"

hexen::engine::core::Scene::Scene(const std::string &name) : name(name) , size(1024.0f) , unitSize(32.0f)
{
    root = memory::make_shared<entity::SceneEntity>(name);

    //temporary , entities will be loaded from file
    root->addChild("Scene_Entity_0");
    root->addChild("Scene_Entity_1");
    root->addChild("Scene_Entity_2");
    root->getChild("Scene_Entity_2")->addChild("Scene_Entity_3");
    root->getChild("Scene_Entity_2")->getChild("Scene_Entity_3")->addChild("Scene_Entity_4");
    root->getChild("Scene_Entity_2")->getChild("Scene_Entity_3")->addChild("Scene_Entity_5");
}

hexen::engine::core::Scene::Scene(const std::string &name, const glm::vec2 &size, const glm::vec2 &unitSize) : Scene(name)
{
    this->unitSize = unitSize;
    this->size = size;
}

hexen::engine::core::Scene::SceneIterator hexen::engine::core::Scene::begin()
{
    return SceneIterator(root,0);
}

hexen::engine::core::Scene::SceneIterator hexen::engine::core::Scene::end()
{
    return SceneIterator(root);
}

hexen::engine::core::Scene::SceneConstantIterator hexen::engine::core::Scene::cbegin() const
{
    return SceneConstantIterator(root, 0);
}

hexen::engine::core::Scene::SceneConstantIterator hexen::engine::core::Scene::cend() const
{
    return SceneConstantIterator(root);
}

hexen::engine::core::Scene::SceneConstantIterator hexen::engine::core::Scene::find(const std::string &UUID) const
{
    return SceneConstantIterator(entity::SceneEntity::getNode(root,UUID));
}

hexen::engine::core::Scene::SceneIterator hexen::engine::core::Scene::find(const std::string &UUID)
{
    return SceneIterator(entity::SceneEntity::getNode(root,UUID));
}

void hexen::engine::core::Scene::erase(const std::string &UUID)
{
    auto it = find(UUID);
    erase(it);
}

void hexen::engine::core::Scene::erase(const core::Scene::SceneIterator &sceneIterator)
{
    if(sceneIterator != end() && sceneIterator->getParent() != nullptr)
    {
        sceneIterator->getParent()->removeChildByUUID(sceneIterator->getUUID());
    }
}

void hexen::engine::core::Scene::forEach(std::function<void(std::shared_ptr<entity::SceneEntity> &)> callback)
{
    for(auto entity : *this)
    {
        callback(entity);
    }
}

std::shared_ptr<hexen::engine::entity::SceneEntity> hexen::engine::core::Scene::getRootNode() const noexcept
{
    return root;
}

hexen::engine::core::Scene::SceneIterator hexen::engine::core::Scene::SceneIterator::operator++(core::i32)
{
    auto tmp = *this;
    ++(*this);
    return tmp;
}

hexen::engine::core::Scene::SceneIterator hexen::engine::core::Scene::SceneIterator::operator--(core::i32)
{
    auto tmp = *this;
    --(*this);
    return tmp;
}

void hexen::engine::core::Scene::SceneIterator::traverseTree(const std::shared_ptr<entity::SceneEntity> &node)
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



std::shared_ptr<hexen::engine::entity::SceneEntity> hexen::engine::core::Scene::SceneIterator::operator->() const
{
    assert(index < visitedNode.size() && "cannot dereference end iterator");
    return entity::SceneEntity::getNode(root,visitedNode[index]);
}

std::shared_ptr<hexen::engine::entity::SceneEntity> hexen::engine::core::Scene::SceneIterator::operator*() const
{
    return operator->();
}

bool hexen::engine::core::Scene::SceneIterator::operator==(const core::Scene::SceneIterator &sceneIterator) const
{
    return root == sceneIterator.root && index == sceneIterator.index;
}

bool hexen::engine::core::Scene::SceneIterator::operator!=(const core::Scene::SceneIterator &sceneIterator) const
{
    return !operator==(sceneIterator);
}

hexen::engine::core::Scene::SceneIterator::SceneIterator(const std::shared_ptr<hexen::engine::entity::SceneEntity> &root,u32 index) : root(root) , index(index)
{
    traverseTree(root);
}

hexen::engine::core::Scene::SceneIterator &hexen::engine::core::Scene::SceneIterator::operator++()
{
    assert(index < visitedNode.size() && "cannot increment end iterator");
    index++;
    return *this;
}

hexen::engine::core::Scene::SceneIterator &hexen::engine::core::Scene::SceneIterator::operator--()
{
    index--;
    return *this;
}

hexen::engine::core::Scene::SceneIterator::SceneIterator(const std::shared_ptr<entity::SceneEntity> &root) : root(root)
{
    traverseTree(root);
    index = visitedNode.size();
}

glm::vec2 hexen::engine::core::Scene::getUnitSize() const noexcept
{
    return unitSize;
}

glm::vec2 hexen::engine::core::Scene::getSize() const noexcept
{
    return size;
}

const std::shared_ptr<hexen::engine::entity::SceneEntity> hexen::engine::core::Scene::SceneConstantIterator::operator->() const
{
    return SceneIterator::operator->();
}

const std::shared_ptr<hexen::engine::entity::SceneEntity> hexen::engine::core::Scene::SceneConstantIterator::operator*() const
{
    return SceneIterator::operator*();
}

hexen::engine::core::Scene::SceneConstantIterator::SceneConstantIterator(const std::shared_ptr<hexen::engine::entity::SceneEntity> &root,u32 index ): SceneIterator(root,index)
{

}

hexen::engine::core::Scene::SceneConstantIterator::SceneConstantIterator(const std::shared_ptr<hexen::engine::entity::SceneEntity> &root) : SceneIterator(root)
{

}

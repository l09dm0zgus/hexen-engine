//
// Created by cx9ps3 on 24.05.2023.
//

#include "Scene.hpp"
#include "../../systems/graphics/RenderSystem.hpp"
#include "../profiling/Profiling.hpp"
#include <algorithm>
#include <assets/AssetsStorage.hpp>
#include <textures/ImageAsset.hpp>
#include <utility>

hexen::engine::core::Scene::Scene(const std::string &name) : name(name), size(1024.0f), unitSize(32.0f)
{
	HEXEN_ADD_TO_PROFILE();
	using namespace hexen::engine::core::assets;

	root = memory::make_shared<entity::SceneEntity>(name);

	//temporary , entities will be loaded from file
	root->addChild<entity::SceneEntity>("Scene_Entity_0");
	root->addChild<entity::SceneEntity>("Scene_Entity_1");
	root->addChild<entity::SceneEntity>("Scene_Entity_2");
	root->getChild("Scene_Entity_2")->addChild<entity::SceneEntity>("Scene_Entity_3");
	root->getChild("Scene_Entity_2")->getChild("Scene_Entity_3")->addChild<entity::SceneEntity>("Scene_Entity_4");
	root->getChild("Scene_Entity_2")->getChild("Scene_Entity_3")->addChild<entity::SceneEntity>("Scene_Entity_5");

	auto componentHandle = systems::RenderSystem::registerNewComponent<components::graphics::SpriteComponent>(AssetHelper::createAsset<graphics::ImageAsset>("images/polpot",std::filesystem::path("textures/polpot.png")));
	auto spriteComponent = systems::RenderSystem::getComponentInstanceByHandle<components::graphics::SpriteComponent>(componentHandle);
	spriteComponent->setOwnerUUID(root->getUUID());

	componentHandle = systems::RenderSystem::registerNewComponent<components::graphics::SpriteComponent>(AssetHelper::createAsset<graphics::ImageAsset>("images/crush",std::filesystem::path("textures/crush.png")));
	spriteComponent = systems::RenderSystem::getComponentInstanceByHandle<components::graphics::SpriteComponent>(componentHandle);
	spriteComponent->setOwnerUUID(root->getChild("Scene_Entity_2")->getUUID());

	componentHandle = systems::RenderSystem::registerNewComponent<components::TransformComponent>(glm::vec2(0));
	auto transformComponent = systems::RenderSystem::getComponentInstanceByHandle<components::TransformComponent>(componentHandle);
	transformComponent->setOwnerUUID(root->getUUID());
	transformComponent->setPosition(glm::vec2(5.0f, -5.0f));

	componentHandle = systems::RenderSystem::registerNewComponent<components::TransformComponent>(glm::vec2(0));
	transformComponent = systems::RenderSystem::getComponentInstanceByHandle<components::TransformComponent>(componentHandle);
	transformComponent->setOwnerUUID(root->getChild("Scene_Entity_2")->getUUID());
	transformComponent->setPosition(glm::vec2(-5.0f, -5.0f));

}

hexen::engine::core::Scene::Scene(const std::string &name, const glm::vec2 &size, const glm::vec2 &unitSize) : Scene(name)
{
	HEXEN_ADD_TO_PROFILE();

	this->unitSize = unitSize;
	this->size = size;
}

hexen::engine::core::Scene::SceneIterator hexen::engine::core::Scene::begin()
{
	HEXEN_ADD_TO_PROFILE();

	return SceneIterator(root, 0);
}

hexen::engine::core::Scene::SceneIterator hexen::engine::core::Scene::end()
{
	HEXEN_ADD_TO_PROFILE();

	return SceneIterator(root);
}

hexen::engine::core::Scene::SceneConstantIterator hexen::engine::core::Scene::cbegin() const
{
	HEXEN_ADD_TO_PROFILE();
	return SceneConstantIterator(root, 0);
}

hexen::engine::core::Scene::SceneConstantIterator hexen::engine::core::Scene::cend() const
{
	HEXEN_ADD_TO_PROFILE();
	return SceneConstantIterator(root);
}

hexen::engine::core::Scene::SceneConstantIterator hexen::engine::core::Scene::find(const std::string &UUID) const
{
	HEXEN_ADD_TO_PROFILE();
	return SceneConstantIterator(entity::SceneEntity::getNode(root, UUID));
}

hexen::engine::core::Scene::SceneIterator hexen::engine::core::Scene::find(const std::string &UUID)
{
	HEXEN_ADD_TO_PROFILE();
	return SceneIterator(entity::SceneEntity::getNode(root, UUID));
}

void hexen::engine::core::Scene::erase(const std::string &UUID)
{
	HEXEN_ADD_TO_PROFILE();
	auto it = find(UUID);
	erase(it);
}

void hexen::engine::core::Scene::erase(const core::Scene::SceneIterator &sceneIterator)
{
	HEXEN_ADD_TO_PROFILE();
	if (sceneIterator != end() && sceneIterator->getParent() != nullptr)
	{
		sceneIterator->getParent()->removeChildByUUID(sceneIterator->getUUID());
	}
}

void hexen::engine::core::Scene::forEach(std::function<void(std::shared_ptr<entity::SceneEntity> &)> callback)
{
	HEXEN_ADD_TO_PROFILE();
	std::for_each(std::execution::par_unseq, this->begin(), this->end(), [&callback](const std::shared_ptr<entity::SceneEntity> &entity)
			{
				//casting entity to non-constant ,because without 'const' in lambda it doesn't  compile ,idk why :(?on cpp reference says std::for_each doesn't care about const in lambda,so problem somewhere in my code :((((
				auto nonConstEntity = (std::shared_ptr<entity::SceneEntity>)entity;
				callback(nonConstEntity); });
}

std::shared_ptr<hexen::engine::entity::SceneEntity> hexen::engine::core::Scene::getRootNode() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return root;
}

hexen::engine::core::Scene::SceneIterator hexen::engine::core::Scene::SceneIterator::operator++(core::i32)
{
	HEXEN_ADD_TO_PROFILE();
	auto tmp = *this;
	++(*this);
	return tmp;
}

hexen::engine::core::Scene::SceneIterator hexen::engine::core::Scene::SceneIterator::operator--(core::i32)
{
	HEXEN_ADD_TO_PROFILE();
	auto tmp = *this;
	--(*this);
	return tmp;
}

void hexen::engine::core::Scene::SceneIterator::traverseTree(const std::shared_ptr<entity::SceneEntity> &node)
{
	HEXEN_ADD_TO_PROFILE();
	auto it = std::find(visitedNode.cbegin(), visitedNode.cend(), node->getUUID());
	if (it == visitedNode.cend())
	{
		visitedNode.push_back(node->getUUID());
	}
	for (auto &child : node->getChildrens())
	{
		traverseTree(child.value);
	}
}

std::shared_ptr<hexen::engine::entity::SceneEntity> hexen::engine::core::Scene::SceneIterator::operator->() const
{
	HEXEN_ADD_TO_PROFILE();
	assert(index < visitedNode.size() && "cannot dereference end iterator");
	return entity::SceneEntity::getNode(root, visitedNode[index]);
}

std::shared_ptr<hexen::engine::entity::SceneEntity> hexen::engine::core::Scene::SceneIterator::operator*() const
{
	HEXEN_ADD_TO_PROFILE();
	return operator->();
}

bool hexen::engine::core::Scene::SceneIterator::operator==(const core::Scene::SceneIterator &sceneIterator) const
{
	HEXEN_ADD_TO_PROFILE();
	return root == sceneIterator.root && index == sceneIterator.index;
}

bool hexen::engine::core::Scene::SceneIterator::operator!=(const core::Scene::SceneIterator &sceneIterator) const
{
	HEXEN_ADD_TO_PROFILE();
	return !operator==(sceneIterator);
}

hexen::engine::core::Scene::SceneIterator::SceneIterator(const std::shared_ptr<hexen::engine::entity::SceneEntity> &root, u32 index) : root(root), index(index)
{
	HEXEN_ADD_TO_PROFILE();
	traverseTree(root);
}

hexen::engine::core::Scene::SceneIterator &hexen::engine::core::Scene::SceneIterator::operator++()
{
	HEXEN_ADD_TO_PROFILE();

	assert(index < visitedNode.size() && "cannot increment end iterator");
	index++;
	return *this;
}

hexen::engine::core::Scene::SceneIterator &hexen::engine::core::Scene::SceneIterator::operator--()
{
	HEXEN_ADD_TO_PROFILE();
	index--;
	return *this;
}

hexen::engine::core::Scene::SceneIterator::SceneIterator(const std::shared_ptr<entity::SceneEntity> &root) : root(root)
{
	HEXEN_ADD_TO_PROFILE();
	traverseTree(root);
	index = visitedNode.size();
}

glm::vec2 hexen::engine::core::Scene::getUnitSize() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return unitSize;
}

glm::vec2 hexen::engine::core::Scene::getSize() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return size;
}

const std::shared_ptr<hexen::engine::entity::SceneEntity> hexen::engine::core::Scene::SceneConstantIterator::operator->() const
{
	HEXEN_ADD_TO_PROFILE();
	return SceneIterator::operator->();
}

const std::shared_ptr<hexen::engine::entity::SceneEntity> hexen::engine::core::Scene::SceneConstantIterator::operator*() const
{
	HEXEN_ADD_TO_PROFILE();
	return SceneIterator::operator*();
}

hexen::engine::core::Scene::SceneConstantIterator::SceneConstantIterator(const std::shared_ptr<hexen::engine::entity::SceneEntity> &root, u32 index) : SceneIterator(root, index)
{
	HEXEN_ADD_TO_PROFILE();
}

hexen::engine::core::Scene::SceneConstantIterator::SceneConstantIterator(const std::shared_ptr<hexen::engine::entity::SceneEntity> &root) : SceneIterator(root)
{
	HEXEN_ADD_TO_PROFILE();
}

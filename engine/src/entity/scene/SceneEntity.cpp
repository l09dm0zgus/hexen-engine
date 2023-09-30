//
// Created by cx9ps3 on 19.05.2023.
//

#include "SceneEntity.h"
#include "../../systems/RenderSystem.hpp"
#include <algorithm>

hexen::engine::entity::SceneEntity::SceneEntity(std::string name) : hexen::engine::entity::Entity(), name(std::move(name))
{
	transformComponent = core::memory::make_shared<components::TransformComponent>();
}
hexen::engine::entity::SceneEntity::SceneEntity(std::string name, const std::string &UUID) : hexen::engine::entity::Entity(UUID), name(std::move(name))
{
	transformComponent = core::memory::make_shared<components::TransformComponent>();
}

hexen::engine::entity::SceneEntity *hexen::engine::entity::SceneEntity::getParent() const noexcept
{
	return parent;
}

void hexen::engine::entity::SceneEntity::setParent(hexen::engine::entity::SceneEntity *newParent)
{
	parent = newParent;
}

void hexen::engine::entity::SceneEntity::forceUpdateTransformMatrix()
{
	if (parent != nullptr)
	{
		transformComponent->updateTransformMatrix(parent->transformComponent->getTransformMatrix());
	}
	else
	{
		transformComponent->updateTransformMatrix();
	}
}

void hexen::engine::entity::SceneEntity::updateTransformMatrix()
{
	if (transformComponent->isDirty())
	{
		forceUpdateTransformMatrix();
		return;
	}

	for (auto &&child : childrens)
	{
		child.value->updateTransformMatrix();
	}
}

void hexen::engine::entity::SceneEntity::removeChild(const std::string &name)
{
	if (hasChildrens())
	{
		auto it = find(name);

		if (it != childrens.cend())
		{
			childrens.remove(it->key);
		}
	}
}

std::string hexen::engine::entity::SceneEntity::getName() const noexcept
{
	return name;
}

void hexen::engine::entity::SceneEntity::removeChildByUUID(const std::string &UUID)
{
	childrens.remove(UUID);
}

bool hexen::engine::entity::SceneEntity::hasChildrens() const noexcept
{
	return !childrens.empty();
}

hexen::engine::core::HashTable<std::string, std::shared_ptr<hexen::engine::entity::SceneEntity>> hexen::engine::entity::SceneEntity::getChildrens() const noexcept
{
	return childrens;
}

std::shared_ptr<hexen::engine::entity::SceneEntity> hexen::engine::entity::SceneEntity::getChild(const std::string &name) const noexcept
{
	auto it = find(name);

	if (it == childrens.cend())
	{
		return nullptr;
	}

	return it->value;
}

std::shared_ptr<hexen::engine::entity::SceneEntity> hexen::engine::entity::SceneEntity::getChildByUUID(const std::string &UUID) const noexcept
{
	auto child = childrens.get(UUID);
	if (child != nullptr)
	{
		return *child;
	}
	else
	{
		return nullptr;
	}
}

hexen::engine::core::HashTable<std::string, std::shared_ptr<hexen::engine::entity::SceneEntity>>::ConstIterator hexen::engine::entity::SceneEntity::find(const std::string &name) const
{
	auto it = std::find_if(childrens.cbegin(), childrens.cend(), [&name](const auto &keyValue)
			{ return name == keyValue.value->getName(); });
	return it;
}

void hexen::engine::entity::SceneEntity::changeParent(std::shared_ptr<SceneEntity> &newParent)
{
	if (newParent != nullptr && newParent.get() != parent && newParent.get() != this)
	{
		if (parent != nullptr)
		{
			auto child = parent->getChildByUUID(getUUID());
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

void hexen::engine::entity::SceneEntity::addChildByPointer(const std::shared_ptr<SceneEntity> &newChild)
{
	childrens.set(newChild->getUUID(), newChild);
}

bool hexen::engine::entity::SceneEntity::isNodeExist(const std::shared_ptr<hexen::engine::entity::SceneEntity> &node, const std::string &UUID)
{
	if (node->getUUID() == UUID)
	{
		return true;
	}
	else
	{
		for (const auto &child : node->childrens)
		{
			if (SceneEntity::isNodeExist(child.value, UUID))
			{
				return true;
			}
		}
	}
	return false;
}

std::shared_ptr<hexen::engine::entity::SceneEntity> hexen::engine::entity::SceneEntity::getNode(const std::shared_ptr<hexen::engine::entity::SceneEntity> &node, const std::string &UUID)
{
	if (node->getUUID() == UUID)
	{
		return node;
	}
	else
	{
		for (const auto &child : node->childrens)
		{
			auto result = SceneEntity::getNode(child.value, UUID);
			if (result != nullptr)
			{
				return result;
			}
		}
	}
	return nullptr;
}

bool hexen::engine::entity::SceneEntity::isDescendantExist(const std::string &descendantUUID)
{
	auto it = childrens.find(descendantUUID);
	if (it != childrens.end())
	{
		return true;
	}
	else
	{
		for (const auto &child : childrens)
		{
			auto isExist = child.value->isDescendantExist(descendantUUID);
			if (isExist)
			{
				return isExist;
			}
		}
	}
	return false;
}

bool hexen::engine::entity::SceneEntity::searchNode(const std::shared_ptr<hexen::engine::entity::SceneEntity> &node, const std::string &searchQuery, core::HashTable<std::string, std::shared_ptr<hexen::engine::entity::SceneEntity>> &foundedNodes)
{
	auto found = node->getName().find(searchQuery);

	if (found != std::string::npos)
	{
		foundedNodes.set(node->getUUID(), node);
		return true;
	}
	else
	{
		for (const auto &child : node->childrens)
		{
			auto result = SceneEntity::searchNode(child.value, searchQuery, foundedNodes);
			if (result)
			{
				return result;
			}
		}
	}
	return false;
}

//
// Created by cx9ps3 on 23.05.2023.
//

#include "RenderSystem.hpp"
#include "TaskSystem.hpp"
#include <algorithm>
#include <execution>

//hexen::engine::components::ComponentContainer<hexen::engine::components::graphics::SpriteComponent,hexen::engine::systems::RenderSystem::COMPONENTS_CONTAINER_SIZE> hexen::engine::systems::RenderSystem::spritesComponent;

//hexen::engine::components::ComponentContainer<hexen::engine::components::graphics::SpriteInstancedComponent,hexen::engine::systems::RenderSystem::COMPONENTS_CONTAINER_SIZE> hexen::engine::systems::RenderSystem::instancedSpritesComponents;

hexen::engine::components::ComponentContainer<hexen::engine::components::TransformComponent,hexen::engine::systems::RenderSystem::COMPONENTS_CONTAINER_SIZE> hexen::engine::systems::RenderSystem::transformComponents;

std::vector<std::shared_ptr<hexen::engine::components::graphics::CameraComponent>> hexen::engine::systems::RenderSystem::camerasComponents;

hexen::engine::core::i32 hexen::engine::systems::RenderSystem::mainCameraId {0};

hexen::engine::systems::RenderSystem::RenderSystem(core::u32 sizeOfVectors)
{
	camerasComponents.reserve(sizeOfVectors);
}


/*
void hexen::engine::systems::RenderSystem::updateSpriteModelMatrix(hexen::engine::components::graphics::SpriteComponent *spriteComponent)
{
 HEXEN_ADD_TO_PROFILE();
	auto iter = std::find_if(std::execution::par,transformComponents.begin(), transformComponents.end(), [sprite = spriteComponent](auto &transform)
			{ return transform.isDirty() && transform.getOwnerUUID() == sprite->getOwnerUUID(); });
	if (iter != transformComponents.end())
	{
		spriteComponent->setTransformMatrix(iter->getTransformMatrix());
	}
}


void hexen::engine::systems::RenderSystem::updateViewAndProjectionMatrices(hexen::engine::components::graphics::SpriteComponent *spriteComponent)
{
 HEXEN_ADD_TO_PROFILE();

	spriteComponent->setProjectionMatrix(camerasComponents[mainCameraId]->getProjectionMatrix());
	spriteComponent->setViewMatrix(camerasComponents[mainCameraId]->getViewMatrix());
}
*/
void hexen::engine::systems::RenderSystem::start()
{
	HEXEN_ADD_TO_PROFILE();
	/*
	for (auto &sprite : spritesComponent)
	{
		TaskSystem::addTask(core::threading::TaskPriority::Normal, this, &RenderSystem::updateSpriteModelMatrix, &sprite);
		TaskSystem::addTask(core::threading::TaskPriority::Normal, this, &RenderSystem::updateViewAndProjectionMatrices, &sprite);
		TaskSystem::addTask<hexen::engine::components::graphics::RenderComponent>(core::threading::TaskPriority::Normal, &sprite, &hexen::engine::components::graphics::SpriteComponent::start);
	}
	for (auto &spriteInstanced : instancedSpritesComponents)
	{
		TaskSystem::addTask<RenderSystem, void, hexen::engine::components::graphics::SpriteComponent *>(core::threading::TaskPriority::Normal, this, &RenderSystem::updateViewAndProjectionMatrices, &spriteInstanced);
		TaskSystem::addTask<hexen::engine::components::graphics::RenderComponent>(core::threading::TaskPriority::Normal, &spriteInstanced, &hexen::engine::components::graphics::SpriteInstancedComponent::start);
	}
	 */
}


void hexen::engine::systems::RenderSystem::render(float alpha)
{
	HEXEN_ADD_TO_PROFILE();

	/*
	for (auto &sprite : spritesComponent)
	{
		TaskSystem::addTask(core::threading::TaskPriority::Normal, this, &RenderSystem::updateSpriteModelMatrix, &sprite);
		TaskSystem::addTask(core::threading::TaskPriority::Normal, this, &RenderSystem::updateViewAndProjectionMatrices, &sprite);
		TaskSystem::addTask<hexen::engine::components::graphics::RenderComponent>(core::threading::TaskPriority::Normal, &sprite, &hexen::engine::components::graphics::SpriteComponent::update, alpha);
	}
	for (auto &spriteInstanced : instancedSpritesComponents)
	{
		TaskSystem::addTask<RenderSystem, void, hexen::engine::components::graphics::SpriteComponent *>(core::threading::TaskPriority::Normal, this, &RenderSystem::updateViewAndProjectionMatrices, &spriteInstanced);
		TaskSystem::addTask<hexen::engine::components::graphics::RenderComponent>(core::threading::TaskPriority::Normal, &spriteInstanced, &hexen::engine::components::graphics::SpriteInstancedComponent::update, alpha);
	}
	 */
}


std::shared_ptr<hexen::engine::components::graphics::CameraComponent> hexen::engine::systems::RenderSystem::getMainCamera()
{
	HEXEN_ADD_TO_PROFILE();
	HEXEN_ASSERT(mainCameraId < camerasComponents.size(), "Failed to get camera.Wrong main camera id!\n");
	if (!camerasComponents.empty())
	{
		return camerasComponents[mainCameraId];
	}

	return nullptr;
}

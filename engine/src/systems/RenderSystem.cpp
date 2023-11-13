//
// Created by cx9ps3 on 23.05.2023.
//

#include "RenderSystem.hpp"
#include "TaskSystem.hpp"
#include <algorithm>
#include <execution>
#include <render_commands/Draw2DQuadsCommand.hpp>
#include <render_commands/RenderPipeline.hpp>
#include <assets/AssetsStorage.hpp>
#include <shaders/ShaderAsset.hpp>

hexen::engine::components::ComponentContainer<hexen::engine::components::graphics::SpriteComponent, hexen::engine::systems::RenderSystem::COMPONENTS_CONTAINER_SIZE> hexen::engine::systems::RenderSystem::spriteComponents;

hexen::engine::components::ComponentContainer<hexen::engine::components::TransformComponent, hexen::engine::systems::RenderSystem::COMPONENTS_CONTAINER_SIZE> hexen::engine::systems::RenderSystem::transformComponents;

std::vector<std::shared_ptr<hexen::engine::components::graphics::CameraComponent>> hexen::engine::systems::RenderSystem::camerasComponents;

hexen::engine::core::i32 hexen::engine::systems::RenderSystem::mainCameraId {0};

hexen::engine::systems::RenderSystem::RenderSystem(core::u32 sizeOfVectors)
{
	HEXEN_ADD_TO_PROFILE();
	camerasComponents.reserve(sizeOfVectors);

	std::vector<std::shared_ptr<graphics::ShaderAsset>> shaders;

	auto vertexShaderAsset = core::assets::AssetsHelper::createAsset<graphics::ShaderAsset>("shaders/BaseQuadVertexShader","shaders/BaseQuadVertex.glsl");
	shaders.push_back(vertexShaderAsset);

	auto fragmentShaderAsset = core::assets::AssetsHelper::createAsset<graphics::ShaderAsset>("shaders/BaseQuadFragmentShader", "shaders/BaseQuadFragment.glsl");
	shaders.push_back(fragmentShaderAsset);

	auto id = engine::graphics::RenderPipeline::addCommandToQueue<engine::graphics::Draw2DQuadsCommand>(shaders);
	draw2DQuadsCommand = engine::graphics::RenderPipeline::getCommandByType<engine::graphics::Draw2DQuadsCommand>(id);
}

void hexen::engine::systems::RenderSystem::render(float alpha)
{
	HEXEN_ADD_TO_PROFILE();
	for (auto &transform : transformComponents)
	{
		transform.updateTransformMatrix();
	}

	for (auto &sprite : spriteComponents)
	{
		TaskSystem::addTask(core::threading::TaskPriority::High, this, &RenderSystem::addSpriteToRender, &sprite);
	}
	TaskSystem::addTask(core::threading::TaskPriority::Normal, this, &RenderSystem::updateViewAndProjectionMatrices);
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

void hexen::engine::systems::RenderSystem::addSpriteToRender(components::graphics::SpriteComponent *spriteComponent)
{
	HEXEN_ADD_TO_PROFILE();
	auto iter = std::find_if(std::execution::par, transformComponents.begin(), transformComponents.end(), [sprite = spriteComponent](auto &transform)
			{ return transform.getOwnerUUID() == sprite->getOwnerUUID(); });

	if (iter != transformComponents.end())
	{
		draw2DQuadsCommand->addQuad(spriteComponent->getTexture(), iter->getTransformMatrix());
	}
}

void hexen::engine::systems::RenderSystem::updateViewAndProjectionMatrices()
{
	HEXEN_ADD_TO_PROFILE();
	draw2DQuadsCommand->updateViewAndProjectionMatrices(camerasComponents[mainCameraId]->getViewMatrix(), camerasComponents[mainCameraId]->getProjectionMatrix());
}

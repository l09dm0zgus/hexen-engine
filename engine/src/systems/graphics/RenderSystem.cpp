//
// Created by cx9ps3 on 23.05.2023.
//

#include "RenderSystem.hpp"
#include <assets/AssetsStorage.hpp>
#include <render_commands/Draw2DQuadsCommand.hpp>
#include <render_commands/RenderPipeline.hpp>
#include <shaders/ShaderAsset.hpp>
#include <algorithm>
#include <execution>

std::vector<std::shared_ptr<hexen::engine::components::graphics::CameraComponent>> hexen::engine::systems::RenderSystem::camerasComponents;
hexen::engine::systems::ComponentsRegistry hexen::engine::systems::RenderSystem::componentsRegistry;

hexen::engine::core::i32 hexen::engine::systems::RenderSystem::mainCameraId {0};

hexen::engine::systems::RenderSystem::RenderSystem(core::u32 sizeOfVectors)
{
	HEXEN_ADD_TO_PROFILE();
	auto transformCallback = [](components::TransformComponent& transformComponent){transformComponent.updateTransformMatrix(); };
	componentsRegistry.addComponentContainer<components::TransformComponent, COMPONENTS_CONTAINER_SIZE>(transformCallback);

	auto spriteCallback = [this](components::graphics::SpriteComponent& spriteComponent){ addSpriteToRender(spriteComponent);};
	componentsRegistry.addComponentContainer<components::graphics::SpriteComponent, COMPONENTS_CONTAINER_SIZE>(spriteCallback);

	camerasComponents.reserve(sizeOfVectors);


}

void hexen::engine::systems::RenderSystem::render(float alpha)
{
	HEXEN_ADD_TO_PROFILE();
	if(firstRun)
	{
		std::vector<std::shared_ptr<graphics::ShaderAsset>> shaders;

		auto vertexShaderAsset = core::assets::AssetHelper::createAsset<graphics::ShaderAsset>("shaders/BaseQuadVertexShader",std::filesystem::path("shaders/BaseQuadVertex.glsl"));
		shaders.push_back(vertexShaderAsset);

		auto fragmentShaderAsset = core::assets::AssetHelper::createAsset<graphics::ShaderAsset>("shaders/BaseQuadFragmentShader", std::filesystem::path("shaders/BaseQuadFragment.glsl"));
		shaders.push_back(fragmentShaderAsset);

		auto id = engine::graphics::RenderPipeline::addCommandToQueue<engine::graphics::Draw2DQuadsCommand>(hexen::engine::graphics::RenderPipelineID::MAIN_PIPELINE, shaders);
		draw2DQuadsCommand = engine::graphics::RenderPipeline::getCommandByType<engine::graphics::Draw2DQuadsCommand>(hexen::engine::graphics::RenderPipelineID::MAIN_PIPELINE, id);

		firstRun = false;
	}
	componentsRegistry.iterateAllContainers();
	threads::TaskSystem::addTask(core::threading::TaskPriority::Normal, this, &RenderSystem::updateViewAndProjectionMatrices);
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

void hexen::engine::systems::RenderSystem::addSpriteToRender(components::graphics::SpriteComponent& spriteComponent)
{
	HEXEN_ADD_TO_PROFILE();
	auto transformComponents = componentsRegistry.getBaseComponentContainer<components::TransformComponent>();
	auto iter = std::find_if(std::execution::par, transformComponents->begin(), transformComponents->end(), [sprite = spriteComponent](auto &transform)
			{ return transform.getOwnerUUID() == sprite.getOwnerUUID(); });

	if (iter != transformComponents->end())
	{
		draw2DQuadsCommand->addQuad(spriteComponent.getTexture(), iter->getTransformMatrix());
	}
}

void hexen::engine::systems::RenderSystem::updateViewAndProjectionMatrices()
{
	HEXEN_ADD_TO_PROFILE();
	draw2DQuadsCommand->updateViewAndProjectionMatrices(camerasComponents[mainCameraId]->getViewMatrix(), camerasComponents[mainCameraId]->getProjectionMatrix());
}

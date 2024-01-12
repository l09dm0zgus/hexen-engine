//
// Created by cx9ps3 on 26.12.2023.
//

#include "ImageComponent.hpp"
#include "../../application/Application.hpp"
#include <render_commands/DrawQuadCommand.hpp>
#include <shaders/ShaderAsset.hpp>

hexen::editor::components::graphics::ImageComponent::ImageComponent(const std::shared_ptr<engine::graphics::ImageAsset> &imageAsset, engine::graphics::RenderPipelineID renderPipelineId)
{
	std::vector<std::shared_ptr<engine::graphics::ShaderAsset>> shadersAssets;
	auto vertexShaderAsset = engine::core::assets::AssetHelper::createAsset<engine::graphics::ShaderAsset>("shaders/BaseVertex", "shaders/BaseVertex.glsl", Application::getName());
	auto fragmentShaderAsset = engine::core::assets::AssetHelper::createAsset<engine::graphics::ShaderAsset>("shaders/BaseFragment", "shaders/BaseFragment.glsl", Application::getName());

	shadersAssets.push_back(vertexShaderAsset);
	shadersAssets.push_back(fragmentShaderAsset);

	auto handle = engine::graphics::RenderPipeline::addCommandToQueue<engine::graphics::DrawQuadCommand>(renderPipelineId, shadersAssets, imageAsset);
	drawQuadCommand = engine::graphics::RenderPipeline::getCommandByType<engine::graphics::DrawQuadCommand>(renderPipelineId, handle);
}

void hexen::editor::components::graphics::ImageComponent::changeImage(const std::shared_ptr<engine::graphics::ImageAsset> &imageAsset)
{
	drawQuadCommand->changeTexture(imageAsset);
}


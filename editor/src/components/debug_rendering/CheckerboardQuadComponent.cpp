//
// Created by cx9ps3 on 20.11.2023.
//

#include "CheckerboardQuadComponent.hpp"
#include "DrawCheckerboardQuad.hpp"
#include <graphics/render_commands/RenderPipeline.hpp>

hexen::editor::components::graphics::CheckerboardQuadComponent::CheckerboardQuadComponent(const std::vector<std::shared_ptr<engine::graphics::ShaderAsset>> &shaderAssets, const glm::vec2 &windowSize, engine::graphics::RenderPipelineID renderPipelineId)
{
	auto renderHandle = engine::graphics::RenderPipeline::addCommandToQueue<DrawCheckerboardQuad>(renderPipelineId, shaderAssets, windowSize);
	drawCheckerboard = engine::graphics::RenderPipeline::getCommandByType<DrawCheckerboardQuad>(renderPipelineId, renderHandle);
}

void hexen::editor::components::graphics::CheckerboardQuadComponent::setWindowSize(const glm::vec2 &windowSize)
{
	drawCheckerboard->setWindowSize(windowSize);
}

void hexen::editor::components::graphics::CheckerboardQuadComponent::setColors(const glm::vec4 &firstColor, const glm::vec4 &secondColor)
{
	drawCheckerboard->setColors(firstColor, secondColor);
}

void hexen::editor::components::graphics::CheckerboardQuadComponent::setViewAndProjectionMatrices(const glm::mat4 &view, const glm::mat4 &projection)
{
	drawCheckerboard->projection = projection;
	drawCheckerboard->view = view;
}

void hexen::editor::components::graphics::CheckerboardQuadComponent::setTransformMatrix(const glm::mat4 &transform)
{
	drawCheckerboard->transform = transform;
}

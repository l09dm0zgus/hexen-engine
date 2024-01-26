//
// Created by cx9ps3 on 13.07.2023.
//

#include "GridComponent.hpp"
#include "DrawGridCommand.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <graphics/render_commands/RenderPipeline.hpp>

hexen::editor::components::graphics::GridComponent::GridComponent(const std::vector<std::shared_ptr<engine::graphics::ShaderAsset>> &shaderAssets, const glm::vec3 &newColor, const glm::vec2 &size, const glm::vec2 &unitSize, hexen::engine::graphics::RenderPipelineID renderPipelineId) : shaderAssets(shaderAssets)
{
	HEXEN_ADD_TO_PROFILE();
	grid = hexen::engine::core::memory::make_shared<hexen::engine::core::Grid>(size,unitSize);

	if (grid != nullptr)
	{
		auto vertices = createGridVertices(grid);
		auto indices = createGridIndices(grid);

		auto renderHandle = engine::graphics::RenderPipeline::addCommandToQueue<DrawGridCommand>(renderPipelineId, RenderGridData(vertices, indices, shaderAssets, newColor));
		drawGridCommand = engine::graphics::RenderPipeline::getCommandByType<DrawGridCommand>(renderPipelineId, renderHandle);
	}
}

void hexen::editor::components::graphics::GridComponent::setViewAndProjectionMatrices(const glm::mat4 &view, const glm::mat4 &projection)
{
	HEXEN_ADD_TO_PROFILE();
	drawGridCommand->view = view;
	drawGridCommand->projection = projection;
}

void hexen::editor::components::graphics::GridComponent::setTransformMatrix(const glm::mat4 &transform)
{
	HEXEN_ADD_TO_PROFILE();
	drawGridCommand->transform = transform;
}

std::vector<glm::vec3> hexen::editor::components::graphics::GridComponent::createGridVertices(const std::shared_ptr<hexen::engine::core::Grid> &grid)
{
	HEXEN_ADD_TO_PROFILE();
	std::vector<glm::vec3> vertices;
	glm::vec4 quadVertexPositions[4];
	float cellWidth = grid->getUnitSize().x;
	float cellHeight = grid->getUnitSize().y;

	float rows = grid->getSize().x;
	float columns = grid->getSize().y;
	float spacing = grid->getSpacingBetweenCells();

	quadVertexPositions[0] = {0.5F, 0.5F, 0.0F, 1.0F};
	quadVertexPositions[1] = {0.5F, -0.5F, 0.0F, 1.0F};
	quadVertexPositions[2] = {-0.5F, -0.5F, 0.0F, 1.0F};
	quadVertexPositions[3] = {-0.5F, 0.5F, 0.0F, 1.0F};

	for (hexen::engine::core::i32 j = 0; j < columns; ++j)
	{
		for (hexen::engine::core::i32 i = 0; i < rows; ++i)
		{
			auto scale = glm::scale(glm::mat4(1.0), glm::vec3( cellWidth / 100, cellHeight / 100, 1.0f));
			auto trans = glm::translate(scale, {i * spacing, j * spacing, 0});
			for(engine::core::u32 k = 0; k < 4; k++)
			{
				auto vertexPosition = trans * quadVertexPositions[k];
				vertices.emplace_back(vertexPosition.x , vertexPosition.y, 0);
			}
		}
	}
	return vertices;
}

std::vector<hexen::engine::core::u32> hexen::editor::components::graphics::GridComponent::createGridIndices(const std::shared_ptr<hexen::engine::core::Grid> &grid)
{
	HEXEN_ADD_TO_PROFILE();
	auto rows = grid->getSize().x;
	auto columns = grid->getSize().y;

	auto numberOfRectangles = rows * columns * 6;

	std::vector<engine::core::u32> indices(numberOfRectangles);

	engine::core::u32 offset = 0;
	for (engine::core::i32 i = 0; i < numberOfRectangles; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	return indices;
}

void hexen::editor::components::graphics::GridComponent::setSize(const glm::vec2 &newSize)
{
	HEXEN_ADD_TO_PROFILE();
	grid->resize(newSize);
	resize();
}

void hexen::editor::components::graphics::GridComponent::setUnitSize(const glm::vec2 &newUnitSize)
{
	HEXEN_ADD_TO_PROFILE();
	grid->setUnitSize(newUnitSize);
	resize();
}

void hexen::editor::components::graphics::GridComponent::setLineWidth(float lineWidth)
{
	HEXEN_ADD_TO_PROFILE();
	drawGridCommand->lineWidth = lineWidth;
}


void hexen::editor::components::graphics::GridComponent::resize()
{
	HEXEN_ADD_TO_PROFILE();
	auto vertices = createGridVertices(grid);
	auto indices = createGridIndices(grid);
	drawGridCommand->resize(RenderGridData(vertices, indices,shaderAssets,color));
}

void hexen::editor::components::graphics::GridComponent::setSpacingBetweenCells(float newSpacing)
{
	HEXEN_ADD_TO_PROFILE();
	grid->setSpacingBetweenCells(newSpacing);
}

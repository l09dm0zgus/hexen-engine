//
// Created by cx9ps3 on 13.07.2023.
//

#include "DebugGridComponent.hpp"
#include <graphics/render_commands/RenderPipeline.hpp>
#include "DrawGridCommand.hpp"

hexen::editor::components::graphics::DebugGridComponent::DebugGridComponent(const std::vector<std::string> &pathsToShaders)
{
	HEXEN_ADD_TO_PROFILE()
	std::vector<glm::vec3> vertices;

	std::vector<glm::uvec4> indices;

	shaderProgram = engine::graphics::ShaderProgram::create(pathsToShaders);

	grid = hexen::engine::core::memory::make_unique<hexen::engine::core::Grid>();

	if (grid != nullptr)
	{
		for (hexen::engine::core::i32 j = 0; j <= grid->getSize().x; ++j)
		{
			for (hexen::engine::core::i32 i = 0; i <= grid->getSize().y; ++i)
			{
				auto x = (float) i - grid->getUnitSize().y / grid->getNumberOfCells();
				auto y = 0;
				auto z = (float) j - grid->getUnitSize().x / grid->getNumberOfCells();
				vertices.emplace_back(x, y, z);
			}
		}

		for (hexen::engine::core::i32 j = 0; j < grid->getSize().x; ++j)
		{
			for (hexen::engine::core::i32 i = 0; i < grid->getSize().y; ++i)
			{

				hexen::engine::core::u32 row1 = j * (grid->getSize().x + 1);
				hexen::engine::core::u32 row2 = (j + 1) * (grid->getSize().y + 1);

				indices.emplace_back(row1 + i, row1 + i + 1, row1 + i + 1, row2 + i + 1);
				indices.emplace_back(row2 + i + 1, row2 + i, row2 + i, row1 + i);
			}
		}
	}

	renderHandle = engine::graphics::RenderPipeline::addCommandToQueue<DrawGridCommand>(RenderGridData(vertices, indices));
}

void hexen::editor::components::graphics::DebugGridComponent::draw() noexcept
{
	HEXEN_ADD_TO_PROFILE()
	shaderProgram->bind();
	shaderProgram->setMatrix4("model", getTransformMatrix());
	shaderProgram->setMatrix4("projection", getProjectionMatrix());
	shaderProgram->setMatrix4("view", getViewMatrix());
	shaderProgram->setVector3f("color", color);

}

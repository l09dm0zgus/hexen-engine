//
// Created by cx9ps3 on 19.10.2023.
//

#include "DrawGridCommand.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <draw_calls/DrawCalls.hpp>

hexen::editor::components::graphics::DrawGridCommand::DrawGridCommand(const RenderGridData& renderGridData) : color(renderGridData.color)
{
	HEXEN_ADD_TO_PROFILE()
	vertexArray = engine::graphics::VertexArray::create();

	elementsBuffer = engine::graphics::ElementsBuffer::create(MAX_GRID_VERTICES * sizeof(glm::vec3));
	vertexBuffer = engine::graphics::VertexBuffer::create(MAX_GRID_INDICES * sizeof(glm::uvec4));

	vertexBuffer->setLayout({
			{ engine::graphics::ShaderDataType::VEC3F , "aPos" }
	});
	vertexArray->addVertexBuffer(vertexBuffer);
	vertexArray->setElementBuffer(elementsBuffer);

	resize(renderGridData);
	shaderProgram = engine::graphics::ShaderProgram::create(renderGridData.shaderAssets);

}

void hexen::editor::components::graphics::DrawGridCommand::prepare()
{
	HEXEN_ADD_TO_PROFILE()
}

void hexen::editor::components::graphics::DrawGridCommand::execute()
{
	HEXEN_ADD_TO_PROFILE()

	shaderProgram->bind();
	shaderProgram->setMatrix4("model", transform);
	shaderProgram->setMatrix4("projection",projection);
	shaderProgram->setMatrix4("view", view);
	shaderProgram->setVector3f("color", color);

	vertexArray->bind();
	engine::graphics::setPolygonRasterization(engine::graphics::PolygonRasterizationMode::LINE);
	engine::graphics::setLineWidth(lineWidth);
	engine::graphics::drawTriangles(countOfTriangles);
	engine::graphics::setPolygonRasterization(engine::graphics::PolygonRasterizationMode::FILL);
	vertexArray->unbind();

}

void hexen::editor::components::graphics::DrawGridCommand::finish()
{
	HEXEN_ADD_TO_PROFILE()
}

void hexen::editor::components::graphics::DrawGridCommand::resize(const hexen::editor::components::graphics::RenderGridData &renderGridData)
{
	elementsBuffer->setData(renderGridData.indices, renderGridData.indicesSize);
	vertexBuffer->setData(renderGridData.vertices, renderGridData.verticesSize);
	countOfTriangles = renderGridData.countOfTriangles;
}

hexen::editor::components::graphics::RenderGridData::RenderGridData(const std::vector<glm::vec3> &verticesVector, const std::vector<engine::core::u32> &indicesVector , const std::vector<std::shared_ptr<engine::graphics::ShaderAsset>>& shaderAssets, const glm::vec3& color) : shaderAssets(shaderAssets), color(color)
{
	HEXEN_ADD_TO_PROFILE()
	vertices = const_cast<float*>(glm::value_ptr(verticesVector[0]));
	indices = const_cast<engine::core::u32*>(indicesVector.data());

	verticesSize = verticesVector.size() * sizeof(glm::vec3);
	indicesSize = indicesVector.size() * sizeof(engine::core::u32);

	countOfTriangles = indicesVector.size();

}

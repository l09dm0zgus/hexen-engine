//
// Created by cx9ps3 on 19.10.2023.
//

#include "DrawGridCommand.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <draw_calls/DrawCalls.hpp>

hexen::editor::graphics::DrawGridCommand::DrawGridCommand(const RenderGridData& renderGridData)
{
	vertexArray = engine::graphics::VertexArray::create();
	elementsBuffer = engine::graphics::ElementsBuffer::create(renderGridData.indices,renderGridData.indicesSize);
	vertexBuffer = engine::graphics::VertexBuffer::create(renderGridData.vertices, renderGridData.verticesSize);
	vertexBuffer->setLayout({
			{ engine::graphics::ShaderDataType::VEC3F , "aPos" }
	});
	vertexArray->addVertexBuffer(vertexBuffer);
	vertexArray->setElementBuffer(elementsBuffer);

	countOfLines = renderGridData.countOfLines;
}

void hexen::editor::graphics::DrawGridCommand::prepare()
{
	vertexArray->bind();
}

void hexen::editor::graphics::DrawGridCommand::execute()
{
	engine::graphics::drawLines(countOfLines);
}

void hexen::editor::graphics::DrawGridCommand::finish()
{
	vertexArray->unbind();
}

hexen::editor::graphics::RenderGridData::RenderGridData(const std::vector<glm::vec3> &verticesVector, const std::vector<glm::uvec4> &indicesVector)
{
	vertices = const_cast<float*>(glm::value_ptr(verticesVector[0]));
	indices = const_cast<engine::core::u32*>(glm::value_ptr(indicesVector[0]));

	verticesSize = verticesVector.size() * sizeof(glm::vec3);
	indicesSize = indicesVector.size() * sizeof(glm::uvec4);

	countOfLines = indicesVector.size() * 4;
}

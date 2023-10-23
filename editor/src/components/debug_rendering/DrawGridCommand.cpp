//
// Created by cx9ps3 on 19.10.2023.
//

#include "DrawGridCommand.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <draw_calls/DrawCalls.hpp>

hexen::editor::components::graphics::DrawGridCommand::DrawGridCommand(const RenderGridData& renderGridData)
{
	HEXEN_ADD_TO_PROFILE()
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

void hexen::editor::components::graphics::DrawGridCommand::prepare()
{
	HEXEN_ADD_TO_PROFILE()
	vertexArray->bind();
}

void hexen::editor::components::graphics::DrawGridCommand::execute()
{
	HEXEN_ADD_TO_PROFILE()
	engine::graphics::drawLines(countOfLines);
}

void hexen::editor::components::graphics::DrawGridCommand::finish()
{
	HEXEN_ADD_TO_PROFILE()
	vertexArray->unbind();
}

hexen::editor::components::graphics::RenderGridData::RenderGridData(const std::vector<glm::vec3> &verticesVector, const std::vector<glm::uvec4> &indicesVector)
{
	HEXEN_ADD_TO_PROFILE()
	vertices = const_cast<float*>(glm::value_ptr(verticesVector[0]));
	indices = const_cast<engine::core::u32*>(glm::value_ptr(indicesVector[0]));

	verticesSize = verticesVector.size() * sizeof(glm::vec3);
	indicesSize = indicesVector.size() * sizeof(glm::uvec4);

	countOfLines = indicesVector.size() * 4;
}

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
	elementsBuffer = engine::graphics::ElementsBuffer::create(renderGridData.indices,renderGridData.indicesSize);
	vertexBuffer = engine::graphics::VertexBuffer::create(renderGridData.vertices, renderGridData.verticesSize);

	vertexBuffer->setLayout({
			{ engine::graphics::ShaderDataType::VEC3F , "aPos" }
	});
	vertexArray->addVertexBuffer(vertexBuffer);
	vertexArray->setElementBuffer(elementsBuffer);

	countOfLines = renderGridData.countOfLines;

	shaderProgram = engine::graphics::ShaderProgram::create(renderGridData.pathsToShaders);
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
	engine::graphics::drawLines(countOfLines);
	vertexArray->unbind();
}

void hexen::editor::components::graphics::DrawGridCommand::finish()
{
	HEXEN_ADD_TO_PROFILE()
}

hexen::editor::components::graphics::RenderGridData::RenderGridData(const std::vector<glm::vec3> &verticesVector, const std::vector<glm::uvec4> &indicesVector , const std::vector<std::string>& pathsToShaders, const glm::vec3& color) : pathsToShaders(pathsToShaders), color(color)
{
	HEXEN_ADD_TO_PROFILE()
	vertices = const_cast<float*>(glm::value_ptr(verticesVector[0]));
	indices = const_cast<engine::core::u32*>(glm::value_ptr(indicesVector[0]));

	verticesSize = verticesVector.size() * sizeof(glm::vec3);
	indicesSize = indicesVector.size() * sizeof(glm::uvec4);

	countOfLines = indicesVector.size() * 4;

}

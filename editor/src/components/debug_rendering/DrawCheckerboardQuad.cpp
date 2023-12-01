//
// Created by cx9ps3 on 20.11.2023.
//

#include "DrawCheckerboardQuad.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <draw_calls/DrawCalls.hpp>
#include <graphics/shaders/ShaderAsset.hpp>
hexen::editor::components::graphics::DrawCheckerboardQuad::DrawCheckerboardQuad(const std::vector<std::shared_ptr<engine::graphics::ShaderAsset>> &shaderAssets, const glm::vec2 &size) : windowSize(size), cellCount(size.x / 10, size.y / 10)
{
	HEXEN_ADD_TO_PROFILE();

	vertexArray = engine::graphics::VertexArray::create();
	elementsBuffer = engine::graphics::ElementsBuffer::create(quadIndices.data(), indicesArraySize * sizeof(engine::core::u32));
	vertexBuffer = engine::graphics::VertexBuffer::create(quadVertices.data(), vertexArraySize * sizeof(float));

	vertexBuffer->setLayout({{engine::graphics::ShaderDataType::VEC3F, "aPos"},
			{engine::graphics::ShaderDataType::VEC2F, "aTextureCoordinates"}});

	vertexArray->addVertexBuffer(vertexBuffer);
	vertexArray->setElementBuffer(elementsBuffer);

	shaderProgram = engine::graphics::ShaderProgram::create(shaderAssets);

}

void hexen::editor::components::graphics::DrawCheckerboardQuad::prepare()
{
	HEXEN_ADD_TO_PROFILE();
}

void hexen::editor::components::graphics::DrawCheckerboardQuad::execute()
{
	HEXEN_ADD_TO_PROFILE();
	shaderProgram->bind();
	shaderProgram->setVector2f("windowSize", windowSize);
	shaderProgram->setVector2f("cellCount", cellCount);
	shaderProgram->setVector4f("firstColor", firstColor);
	shaderProgram->setVector4f("secondColor", secondColor);

	shaderProgram->setMatrix4("model", transform);
	shaderProgram->setMatrix4("projection",projection);
	shaderProgram->setMatrix4("view", view);

	vertexArray->bind();
	engine::graphics::drawTriangles(indicesArraySize);
	vertexArray->unbind();
}

void hexen::editor::components::graphics::DrawCheckerboardQuad::finish()
{
	HEXEN_ADD_TO_PROFILE();
}

void hexen::editor::components::graphics::DrawCheckerboardQuad::setWindowSize(const glm::vec2 &newWindowSize)
{
	HEXEN_ADD_TO_PROFILE();
	windowSize = newWindowSize;
	cellCount = {newWindowSize.x / 10, newWindowSize.y / 10};
}

void hexen::editor::components::graphics::DrawCheckerboardQuad::setColors(const glm::vec4 &newFirstColor, const glm::vec4 &newSecondColor)
{
	firstColor = newFirstColor;
	secondColor = newSecondColor;
}

//
// Created by cx9ps3 on 20.11.2023.
//

#include "DrawCheckerboardQuad.hpp"
#include <draw_calls/DrawCalls.hpp>

hexen::editor::components::graphics::DrawCheckerboardQuad::DrawCheckerboardQuad(const std::vector<std::shared_ptr<engine::graphics::ShaderAsset>> &shaderAssets, hexen::engine::core::i32 size) : size(size)
{
	HEXEN_ADD_TO_PROFILE();
	vertexArray = engine::graphics::VertexArray::create();
	elementsBuffer = engine::graphics::ElementsBuffer::create(quadIndices.data(),indicesArraySize);
	vertexBuffer = engine::graphics::VertexBuffer::create(quadVertices.data(), vertexArraySize);

	vertexBuffer->setLayout({
			{ engine::graphics::ShaderDataType::VEC3F , "aPos" },
			{ engine::graphics::ShaderDataType::VEC2F , "aTextureCoordinates"}
	});

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
	shaderProgram->setFloat("size", size);

	vertexArray->bind();
	engine::graphics::drawTriangles(indicesArraySize);
	vertexArray->unbind();
}

void hexen::editor::components::graphics::DrawCheckerboardQuad::finish()
{
	HEXEN_ADD_TO_PROFILE();
}

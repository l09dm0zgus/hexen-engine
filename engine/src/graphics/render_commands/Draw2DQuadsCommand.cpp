//
// Created by cx9ps3 on 23.10.2023.
//

#include "Draw2DQuadsCommand.hpp"
#include "../buffers/Buffers.hpp"
#include "../buffers/VertexArray.hpp"
#include "../shaders/ShaderProgram.hpp"

hexen::engine::graphics::Draw2DQuadsCommand::Draw2DQuadsCommand(const std::initializer_list<std::string> &pathsToShaders)
{
	HEXEN_ADD_TO_PROFILE();
	shaderProgram = ShaderProgram::create(pathsToShaders);
	initializeBuffers();
}

hexen::engine::graphics::Draw2DQuadsCommand::Draw2DQuadsCommand(const std::vector<std::string> &pathsToShaders)
{
	HEXEN_ADD_TO_PROFILE();
	shaderProgram = ShaderProgram::create(pathsToShaders);
	initializeBuffers();
}

void hexen::engine::graphics::Draw2DQuadsCommand::initializeBuffers()
{
	HEXEN_ADD_TO_PROFILE();
	vertexArray = VertexArray::create();
	vertexBuffer = VertexBuffer::create(maxVertices  * sizeof(QuadVertex));
	vertexBuffer->setLayout({
			{ShaderDataType::VEC3F , "aPosition"},
			{ShaderDataType::VEC2F, "aTextureCoordinates"},
	});

	vertexArray->addVertexBuffer(vertexBuffer);

	quadsVertexBase = new QuadVertex[maxVertices];

	auto indices = new core::u32[maxIndices];

	core::u32 offset = 0;
	for (uint32_t i = 0; i < maxIndices; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	auto elementsBuffer = ElementsBuffer::create(indices,maxIndices);
	vertexArray->setElementBuffer(elementsBuffer);

	delete[] indices;
}

hexen::engine::graphics::Draw2DQuadsCommand::~Draw2DQuadsCommand()
{
	delete[] quadsVertexBase;
}

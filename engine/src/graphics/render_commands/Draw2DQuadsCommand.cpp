//
// Created by cx9ps3 on 23.10.2023.
//

#include "Draw2DQuadsCommand.hpp"
#include "../buffers/Buffers.hpp"
#include "../buffers/VertexArray.hpp"
#include "../shaders/ShaderProgram.hpp"
#include "draw_calls/DrawCalls.hpp"
#include "../textures/Texture.hpp"

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
	// used for optimization , see IRenderCommand and RenderPipeline class for details.
	enableExecute = true;
	enableFinish = true;
	enablePrepare = true;

	HEXEN_ADD_TO_PROFILE();
	vertexArray = VertexArray::create();
	vertexBuffer = VertexBuffer::create(maxVertices * sizeof(QuadVertex));
	vertexBuffer->setLayout({{ShaderDataType::VEC3F, "aPosition"},
			{ShaderDataType::VEC2F, "aTextureCoordinates"},
			{ShaderDataType::FLOAT, "aTextureIndex"}});

	vertexArray->addVertexBuffer(vertexBuffer);

	quadsVertexBase = new QuadVertex[maxVertices];
	quadsVertexPointer = quadsVertexBase;

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

	core::i32 samples[maxTextureSlots];

	for (core::i32  i = 0; i < maxTextureSlots; i++)
	{
		samples[i] = i;
	}

	shaderProgram->bind();
	shaderProgram->setIntegerArray("textures" , samples, maxTextureSlots);

	auto elementsBuffer = ElementsBuffer::create(indices, maxIndices);
	vertexArray->setElementBuffer(elementsBuffer);

	quadVertexPositions[0] = {0.5f, 0.5f, 0.0f, 1.0f};
	quadVertexPositions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
	quadVertexPositions[2] = {-0.5f, -0.5f, 0.0f, 1.0f};
	quadVertexPositions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};

	delete[] indices;
}

hexen::engine::graphics::Draw2DQuadsCommand::~Draw2DQuadsCommand()
{
	HEXEN_ADD_TO_PROFILE();
	delete[] quadsVertexBase;
}

void hexen::engine::graphics::Draw2DQuadsCommand::prepare()
{
	HEXEN_ADD_TO_PROFILE();
	std::cout << "Step 1: Binding shader\n";
	vertexArray->bind();
	startBatch();
}
void hexen::engine::graphics::Draw2DQuadsCommand::execute()
{
	drawBatch();
}

void hexen::engine::graphics::Draw2DQuadsCommand::finish()
{
	HEXEN_ADD_TO_PROFILE();

	vertexArray->unbind();
}

void hexen::engine::graphics::Draw2DQuadsCommand::addQuad(const std::shared_ptr<Texture2D> &texture, const glm::mat4 &transform)
{
	HEXEN_ADD_TO_PROFILE();
	std::cout << "Step 3: Add quads.\n";
	constexpr size_t quadVertexCount = 4;
	constexpr glm::vec2 textureCoords[] = {{1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f}};

	if (indexCount >= maxIndices)
	{
		nextBatch();
	}

	float textureIndex = 0.0f;
	for (core::u32 i = 0; i < textureSlotIndex; i++)
	{
		if (textureSlots[i]->getId() == texture->getId())
		{
			textureIndex = (float) i;
			break;
		}
	}

	if (textureIndex == 0.0f)
	{
		if (textureSlotIndex >= maxTextureSlots)
		{
			nextBatch();
		}

		textureIndex = (float) textureSlotIndex;
		textureSlots[textureSlotIndex] = texture;
		textureSlotIndex++;
	}

	for (size_t i = 0; i < quadVertexCount; i++)
	{
		quadsVertexPointer->position = transform * quadVertexPositions[i];
		quadsVertexPointer->textureCoordinates = textureCoords[i];
		quadsVertexPointer->textureIndex = textureIndex;
		quadsVertexPointer++;
	}

	indexCount += 6;
}

void hexen::engine::graphics::Draw2DQuadsCommand::startBatch()
{
	HEXEN_ADD_TO_PROFILE();
	std::cout << "Step 2: Start Batch\n";
	textureSlotIndex = 0;
	indexCount = 0;
	quadsVertexPointer = quadsVertexBase;
}
void hexen::engine::graphics::Draw2DQuadsCommand::drawBatch()
{
	HEXEN_ADD_TO_PROFILE();
	std::cout << "Step 4: Draw batch\n";
	auto dataSize = (core::u32)((core::u8*)quadsVertexPointer - (core::u8*)quadsVertexBase);
	vertexBuffer->setData(quadsVertexBase, dataSize);

	shaderProgram->bind();
	shaderProgram->setMatrix4("view", view);
	shaderProgram->setMatrix4("projection", projection);

	for (core::u32 i = 0; i < textureSlotIndex; i++)
	{
		std::cout << "Bind texture slot: " << i << std::endl;
		textureSlots[i]->bind(i);
	}

	drawTriangles(indexCount);

}

void hexen::engine::graphics::Draw2DQuadsCommand::nextBatch()
{
	HEXEN_ADD_TO_PROFILE();
	drawBatch();
	startBatch();
}

void hexen::engine::graphics::Draw2DQuadsCommand::updateViewAndProjectionMatrices(glm::mat4 &&view, glm::mat4 &&projection)
{
	this->view = view;
	this->projection = projection;
}

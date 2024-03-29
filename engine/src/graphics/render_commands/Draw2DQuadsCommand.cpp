//
// Created by cx9ps3 on 23.10.2023.
//

#include "Draw2DQuadsCommand.hpp"
#include "../buffers/Buffers.hpp"
#include "../buffers/VertexArray.hpp"
#include "../shaders/ShaderProgram.hpp"
#include "../textures/Texture.hpp"
#include "draw_calls/DrawCalls.hpp"
#include <algorithm>
#include <execution>
#include "../textures/ImageAsset.hpp"

hexen::engine::graphics::Draw2DQuadsCommand::Draw2DQuadsCommand(const std::initializer_list<std::shared_ptr<ShaderAsset>> &shadersAssets)
{
	HEXEN_ADD_TO_PROFILE();
	shaderProgram = ShaderProgram::create(shadersAssets);
	initializeBuffers();
}

hexen::engine::graphics::Draw2DQuadsCommand::Draw2DQuadsCommand(const std::vector<std::shared_ptr<ShaderAsset>> &shadersAssets)
{
	HEXEN_ADD_TO_PROFILE();
	shaderProgram = ShaderProgram::create(shadersAssets);
	initializeBuffers();
}

void hexen::engine::graphics::Draw2DQuadsCommand::initializeBuffers()
{
	// used for optimization , see IRenderCommand and RenderPipeline class for details.
	enableExecute = true;
	enableFinish = false;
	enablePrepare = true;

	HEXEN_ADD_TO_PROFILE();
	textureArray = TextureArray::create(maxTextureSize,TextureFilter::NEAREST);
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

	shaderProgram->bind();
	shaderProgram->setInteger("textures", static_cast<core::i32>(TextureArray::getCountOfTextureUnits()));

	auto elementsBuffer = ElementsBuffer::create(indices, maxIndices);
	vertexArray->setElementBuffer(elementsBuffer);

	quadVertexPositions[0] = {0.5F, 0.5F, 0.0F, 1.0F};
	quadVertexPositions[1] = {0.5F, -0.5F, 0.0F, 1.0F};
	quadVertexPositions[2] = {-0.5F, -0.5F, 0.0F, 1.0F};
	quadVertexPositions[3] = {-0.5F, 0.5F, 0.0F, 1.0F};

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
	startBatch();
}
void hexen::engine::graphics::Draw2DQuadsCommand::execute()
{
	HEXEN_ADD_TO_PROFILE();
	setDataToVertexBuffer();
	drawBatch();
}

void hexen::engine::graphics::Draw2DQuadsCommand::finish()
{
	HEXEN_ADD_TO_PROFILE();
}

void hexen::engine::graphics::Draw2DQuadsCommand::addQuad(const std::shared_ptr<ImageAsset> &imageAsset, const glm::mat4 &transform)
{
	HEXEN_ADD_TO_PROFILE();
	quadsData.emplace_back(imageAsset, transform);
}

void hexen::engine::graphics::Draw2DQuadsCommand::startBatch()
{
	HEXEN_ADD_TO_PROFILE();
	textureSlotIndex = 0;
	indexCount = 0;
	quadsVertexPointer = quadsVertexBase;
}
void hexen::engine::graphics::Draw2DQuadsCommand::drawBatch()
{
	HEXEN_ADD_TO_PROFILE();
	shaderProgram->bind();
	shaderProgram->setMatrix4("view", view);
	shaderProgram->setMatrix4("projection", projection);
	shaderProgram->setInteger("textures", static_cast<core::i32>(TextureArray::getCountOfTextureUnits()));

	for(core::u32 i = 0; i < textureSlots.size(); i++)
	{
		textureArray->bind(i);
	}

	vertexArray->bind();
	drawTriangles(indexCount);
	vertexArray->unbind();
}

void hexen::engine::graphics::Draw2DQuadsCommand::nextBatch()
{
	HEXEN_ADD_TO_PROFILE();
	drawBatch();
	startBatch();
}

void hexen::engine::graphics::Draw2DQuadsCommand::updateViewAndProjectionMatrices(glm::mat4 &&view, glm::mat4 &&projection)
{
	HEXEN_ADD_TO_PROFILE();
	this->view = view;
	this->projection = projection;
}

void hexen::engine::graphics::Draw2DQuadsCommand::setDataToVertexBuffer()
{
	HEXEN_ADD_TO_PROFILE();
	std::for_each(quadsData.cbegin(), quadsData.cend(), [this](const auto &quadData)
			{ this->addQuadDataToVertexBuffer(quadData); });
	quadsData.clear();
	auto dataSize = (core::u32)((core::u8 *) quadsVertexPointer - (core::u8 *) quadsVertexBase);
	vertexBuffer->setData(quadsVertexBase, dataSize);
}

void hexen::engine::graphics::Draw2DQuadsCommand::addQuadDataToVertexBuffer(const hexen::engine::graphics::Draw2DQuadsCommand::QuadData &quadData)
{
	HEXEN_ADD_TO_PROFILE();
	constexpr size_t quadVertexCount = 4;
	static const glm::vec2 textureCoords[] = {{1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f}};

	if (indexCount >= maxIndices)
	{
		nextBatch();
	}

	if(textureSlots.find(quadData.first->getName()) == textureSlots.cend())
	{
		textureArray->addTextureToArray(quadData.first, true);
		textureSlots[quadData.first->getName()] = textureSlotIndex;
		textureSlotIndex++;
	}

	for (size_t i = 0; i < quadVertexCount; i++)
	{
		quadsVertexPointer->position = quadData.second * quadVertexPositions[i];
		quadsVertexPointer->textureCoordinates = textureCoords[i];
		quadsVertexPointer->textureIndex = textureSlots[quadData.first->getName()];
		quadsVertexPointer++;
	}

	indexCount += 6;
}

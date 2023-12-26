//
// Created by cx9ps3 on 26.12.2023.
//
#include "DrawQuadCommand.hpp"
#include "buffers/Buffers.hpp"
#include "buffers/VertexArray.hpp"
#include "draw_calls/DrawCalls.hpp"
#include "shaders/ShaderProgram.hpp"
#include "textures/Texture.hpp"

hexen::engine::graphics::DrawQuadCommand::DrawQuadCommand(const std::vector<std::shared_ptr<ShaderAsset>> &shaderAssets, const std::shared_ptr<ImageAsset> &textureImage)
{
	HEXEN_ADD_TO_PROFILE();

	vertexArray = VertexArray::create();
	elementsBuffer = ElementsBuffer::create(quadIndices.data(), indicesArraySize * sizeof(engine::core::u32));
	vertexBuffer = VertexBuffer::create(quadVertices.data(), vertexArraySize * sizeof(float));

	vertexBuffer->setLayout({{ShaderDataType::VEC3F, "aPos"},
			{ShaderDataType::VEC2F, "aTextureCoordinates"}});

	vertexArray->addVertexBuffer(vertexBuffer);
	vertexArray->setElementBuffer(elementsBuffer);

	shaderProgram = ShaderProgram::create(shaderAssets);
	mainTexture = Texture2D::create(textureImage, TextureFilter::NEAREST);
}

void hexen::engine::graphics::DrawQuadCommand::execute()
{
	HEXEN_ADD_TO_PROFILE();
	shaderProgram->bind();
	shaderProgram->setMatrix4("model", transform);
	shaderProgram->setMatrix4("projection", projection);
	shaderProgram->setMatrix4("view", view);

	vertexArray->bind();
	mainTexture->bind();
	drawTriangles(indicesArraySize);
	vertexArray->unbind();
}

void hexen::engine::graphics::DrawQuadCommand::prepare()
{
	HEXEN_ADD_TO_PROFILE();
}

void hexen::engine::graphics::DrawQuadCommand::finish()
{
	HEXEN_ADD_TO_PROFILE();
}

void hexen::engine::graphics::DrawQuadCommand::changeTexture(const std::shared_ptr<ImageAsset> &textureImage)
{
	mainTexture = Texture2D::create(textureImage, TextureFilter::NEAREST);
}

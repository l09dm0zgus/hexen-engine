//
// Created by cx9ps3 on 23.10.2023.
//

#pragma once
#include "IRenderCommand.hpp"
#include <glm/glm.hpp>

namespace hexen::engine::graphics
{
	class ShaderProgram;
	class VertexArray;
	class VertexBuffer;

	struct QuadVertex
	{
		glm::vec3 position;
		glm::vec2 textureCoordinates;
	};

	class Draw2DQuadsCommand : public IRenderCommand
	{
	private:
		const core::u32 maxQuads = 10000;
		const core::u32 maxVertices = maxQuads * 4;
		const core::u32 maxIndices = maxQuads * 6;

		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<VertexArray> vertexArray;
		std::shared_ptr<ShaderProgram> shaderProgram;
		QuadVertex  *quadsVertexBase = nullptr;
		QuadVertex *quadsVertexPointer = nullptr;


		void initializeBuffers();
	public:
		~Draw2DQuadsCommand() override;
		Draw2DQuadsCommand(const std::initializer_list<std::string> &pathsToShaders);
		explicit Draw2DQuadsCommand(const std::vector<std::string> &pathsToShaders);
		void prepare() override;
		void execute() override;
		void finish() override;
	};
}



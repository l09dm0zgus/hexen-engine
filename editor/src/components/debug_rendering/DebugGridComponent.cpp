//
// Created by cx9ps3 on 13.07.2023.
//

#include "DebugGridComponent.hpp"

#ifndef __ANDROID__
	#include <GL/glew.h>
#else
	#include <GLES3/gl31.h>
#endif

hexen::editor::components::graphics::DebugGridComponent::DebugGridComponent(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{
	shaderProgram = hexen::engine::core::memory::make_shared<hexen::engine::graphics::gl::shader::ShaderProgram>(vertexShaderPath, fragmentShaderPath);

	grid = hexen::engine::core::memory::make_unique<hexen::engine::core::Grid>();

	if (grid != nullptr)
	{
		for (hexen::engine::core::i32 j = 0; j <= grid->getSize().x; ++j)
		{
			for (hexen::engine::core::i32 i = 0; i <= grid->getSize().y; ++i)
			{
				auto x = (float) i - grid->getUnitSize().y / grid->getNumberOfCells();
				auto y = 0;
				auto z = (float) j - grid->getUnitSize().x / grid->getNumberOfCells();
				vertices.emplace_back(x, y, z);
			}
		}

		for (hexen::engine::core::i32 j = 0; j < grid->getSize().x; ++j)
		{
			for (hexen::engine::core::i32 i = 0; i < grid->getSize().y; ++i)
			{

				hexen::engine::core::u32 row1 = j * (grid->getSize().x + 1);
				hexen::engine::core::u32 row2 = (j + 1) * (grid->getSize().y + 1);

				indices.emplace_back(row1 + i, row1 + i + 1, row1 + i + 1, row2 + i + 1);
				indices.emplace_back(row2 + i + 1, row2 + i, row2 + i, row1 + i);
			}
		}
	}

	VAO.bind();
	VBO.bind(vertices);
	EBO.bind(indices);
	attributes.add(3, 3, 0);
	VBO.unbind();
	VAO.unbind();
	EBO.unbind();

	lenght = indices.size() * 4;
}

void hexen::editor::components::graphics::DebugGridComponent::draw() noexcept
{
	glEnable(GL_DEPTH_TEST);

	shaderProgram->use();
	shaderProgram->setMatrix4Uniform("model", getTransformMatrix());
	shaderProgram->setMatrix4Uniform("projection", getProjectionMatrix());
	shaderProgram->setMatrix4Uniform("view", getViewMatrix());
	shaderProgram->setVector3Uniform("color", color);


	VAO.bind();

	glDrawElements(GL_LINES, lenght, GL_UNSIGNED_INT, nullptr);

	VAO.unbind();

	glDisable(GL_DEPTH_TEST);
}

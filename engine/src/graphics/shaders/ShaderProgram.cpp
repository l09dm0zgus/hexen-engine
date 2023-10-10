//
// Created by cx9ps3 on 09.10.2023.
//

#include "ShaderProgram.hpp"
std::shared_ptr<hexen::engine::graphics::ShaderProgram> hexen::engine::graphics::ShaderProgram::create(std::vector<std::string> &pathsToShaders)
{
	return std::shared_ptr<GLShaderProgram>();
}

//
// Created by cx9ps3 on 03.01.23.
//

#include "GLShaderProgram.hpp"
#include "SDL3/SDL.h"

#ifndef __ANDROID__
	#include "GL/glew.h"
#else
	#include <GLES3/gl31.h>
#endif
#include "glm/gtc/type_ptr.hpp"

#include <vector>

hexen::engine::graphics::gl::GLShaderProgram::GLShaderProgram(std::vector<std::string> &shadersFiles)
{
	vertexShaderFile.read(vertexShaderPath);
	fragmentShaderFile.read(fragmentShaderPath);
	compileVertexShader();
	compileFragmentShader();
	linkShaders();
}

void hexen::engine::graphics::gl::GLShaderProgram::compileVertexShader()
{
	vertexShaderText = vertexShaderFile.getContent();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderText, nullptr);
	glCompileShader(vertexShader);
	showCompilerLog(vertexShader);
}

inline void hexen::engine::graphics::gl::GLShaderProgram::showCompilerLog(core::u32 shader) const noexcept
{
	core::i32 success {0};
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		SDL_Log("Error:Failed compile shader.What : %s", infoLog);
	}
}

inline void hexen::engine::graphics::gl::GLShaderProgram::compileFragmentShader()
{
	fragmentShaderText = fragmentShaderFile.getContent();
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderText, nullptr);
	glCompileShader(fragmentShader);
	showCompilerLog(fragmentShader);
}

hexen::engine::graphics::gl::GLShaderProgram::~GLShaderProgram()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void hexen::engine::graphics::gl::GLShaderProgram::linkShaders()
{
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	showLinkerLog();
}

void hexen::engine::graphics::gl::GLShaderProgram::showLinkerLog() const noexcept
{
	core::i32 success {0};
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		SDL_Log("Error:Failed to link shader.What : %s", infoLog);
	}
}

void hexen::engine::graphics::gl::GLShaderProgram::use() const noexcept
{
	glUseProgram(shaderProgram);
}

void hexen::engine::graphics::gl::GLShaderProgram::setIntUniform(const std::string &uniformVariable, core::i32 value) const
{
	glUniform1i(glGetUniformLocation(shaderProgram, uniformVariable.c_str()), value);
}

void hexen::engine::graphics::gl::GLShaderProgram::setMatrix4Uniform(const std::string &uniformVariable, const glm::mat4 &matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniformVariable.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void hexen::engine::graphics::gl::GLShaderProgram::setVector4Uniform(const std::string &uniformVariable, const glm::vec4 &vector) const
{
	glUniform4f(glGetUniformLocation(shaderProgram, uniformVariable.c_str()), vector.x, vector.y, vector.z, vector.w);
}

void hexen::engine::graphics::gl::GLShaderProgram::setVector3Uniform(const std::string &uniformVariable, const glm::vec3 &vector) const
{
	glUniform3f(glGetUniformLocation(shaderProgram, uniformVariable.c_str()), vector.x, vector.y, vector.z);
}
void hexen::engine::graphics::gl::GLShaderProgram::shaderPathsToShaderFiles(const std::vector<std::string> &paths)
{

}

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

namespace hexen::engine::graphics::gl
{
	static GLenum shaderTypeToGLShaderType(ShaderType type)
	{
		switch (type)
		{
			case ShaderType::UNKNOWN:
				break;
			case ShaderType::VERTEX:
				return GL_VERTEX_SHADER;
				break;
			case ShaderType::GEOMETRY:
				return GL_GEOMETRY_SHADER;
				break;
			case ShaderType::FRAGMENT:
				return GL_FRAGMENT_SHADER;
				break;
		}
		HEXEN_ASSERT(false,"ERROR: Wrong shader type!");
	}
}


hexen::engine::graphics::gl::GLShaderProgram::GLShaderProgram(const std::vector<std::string> &shadersFiles)
{
	for(const auto& pathToShader : shadersFiles)
	{
		ShaderFile shaderFile;
		shaderFile.read(pathToShader);
		shadersData.push_back(shaderFile);
	}

	compileShaders();
	linkShaders();
}

HEXEN_INLINE void hexen::engine::graphics::gl::GLShaderProgram::showCompilerLog(core::u32 shader) const noexcept
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

hexen::engine::graphics::gl::GLShaderProgram::~GLShaderProgram()
{
	for(auto id : shadersIds)
	{
		glDeleteShader(id);
	}
}

void hexen::engine::graphics::gl::GLShaderProgram::linkShaders()
{
	shaderProgram = glCreateProgram();
	for(auto id : shadersIds)
	{
		glAttachShader(shaderProgram, id);
	}
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

void hexen::engine::graphics::gl::GLShaderProgram::bind() const
{
	glUseProgram(shaderProgram);
}

void hexen::engine::graphics::gl::GLShaderProgram::compileShader(const hexen::engine::graphics::ShaderFile &shaderFile)
{
	auto shaderText = shaderFile.getContent();
	auto shaderId = glCreateShader(shaderTypeToGLShaderType(shaderFile.getType()));
	glShaderSource(shaderId, 1, &shaderText, nullptr);
	glCompileShader(shaderId);
	showCompilerLog(shaderId);
	shadersIds.push_back(shaderId);
}
void hexen::engine::graphics::gl::GLShaderProgram::compileShaders()
{
	for(const auto& shaderFile : shadersData)
	{
		compileShader(shaderFile);
	}
}

void hexen::engine::graphics::gl::GLShaderProgram::unbind() const
{
	glUseProgram(0);
}

void hexen::engine::graphics::gl::GLShaderProgram::setVector2f(const std::string &name, const glm::vec2 &value) const
{
	glUniform2f(glGetUniformLocation(shaderProgram,name.c_str()),value.x,value.y);
}

void hexen::engine::graphics::gl::GLShaderProgram::setVector3f(const std::string &name, const glm::vec3 &value) const
{
	glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), value.x, value.y, value.z);
}

void hexen::engine::graphics::gl::GLShaderProgram::setVector4f(const std::string &name, const glm::vec4 &value) const
{
	glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), value.x, value.y, value.z, value.w);
}

void hexen::engine::graphics::gl::GLShaderProgram::setMatrix2(const std::string &name, const glm::mat2 &value) const
{
	glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void hexen::engine::graphics::gl::GLShaderProgram::setMatrix3(const std::string &name, const glm::mat3 &value) const
{
	glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void hexen::engine::graphics::gl::GLShaderProgram::setMatrix4(const std::string &name, const glm::mat4 &value) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void hexen::engine::graphics::gl::GLShaderProgram::setInteger(const std::string &name, hexen::engine::core::i32 value) const
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void hexen::engine::graphics::gl::GLShaderProgram::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

//
// Created by cx9ps3 on 03.01.23.
//

#include "ShaderFile.hpp"
#include "../render_context/RenderContext.hpp"
#include "SDL3/SDL.h"
#include "../profiling/Profiling.hpp"

void hexen::engine::graphics::ShaderFile::read(const std::string &path)
{
	HEXEN_ADD_TO_PROFILE();
	SDL_RWops *file = SDL_RWFromFile(path.c_str(), "r");
	if (file != nullptr)
	{
		int size = SDL_RWsize(file);
		SDL_Log("ShaderFile file size : %d", size);
		char *shaderData = new char[size];
		if (SDL_RWread(file, shaderData, size) < 0)
		{
			SDL_Log("Failed to read %s shader.\n", path.c_str());
		}

		shaderText.assign(shaderData, size);
		SDL_Log("Shader %s code : %s", path.c_str(), shaderText.c_str());

		delete[] shaderData;
		shaderData = nullptr;
	}
	else
	{
		SDL_Log("Failed to open %s shader.\n", path.c_str());
	}
	SDL_RWclose(file);

	auto stringShaderType = parseShaderType();
	setShaderType(stringShaderType);
}

char *hexen::engine::graphics::ShaderFile::getContent() const
{
	HEXEN_ADD_TO_PROFILE();
	return const_cast<char *>(shaderText.c_str());
}

std::string hexen::engine::graphics::ShaderFile::parseShaderType()
{
	HEXEN_ADD_TO_PROFILE();
	std::string typeToken = "#type";
	auto tokenPosition = shaderText.find(typeToken);
	HEXEN_ASSERT(tokenPosition != std::string::npos, "ERROR: Token #type in shader file " + path + " not found! Please specify shader type!");
	std::string buffer;

	for (auto i = tokenPosition; i < shaderText.size(); i++)
	{
		buffer += shaderText[i];
		if (shaderText[i] == '\n')
		{
			break;
		}
	}

	tokenPosition = shaderText.find(buffer);
	shaderText.erase(tokenPosition, buffer.size());

	std::string token = buffer.substr(typeToken.size(), buffer.size());

	token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
	token.erase(std::remove(token.begin(), token.end(), '\r'), token.end());
	token.erase(std::remove(token.begin(), token.end(), '\n'), token.end());

	return token;
}
void hexen::engine::graphics::ShaderFile::setShaderType(const std::string &shaderType)
{
	HEXEN_ADD_TO_PROFILE();
	if (shaderType == "vertex")
	{
		type = ShaderType::VERTEX;
	}
	else if (shaderType == "fragment" || shaderType == "pixel")
	{
		type = ShaderType::FRAGMENT;
	}
	else if (shaderType == "geometry")
	{
		type = ShaderType::GEOMETRY;
	}
	else
	{
		type = ShaderType::UNKNOWN;
		HEXEN_ASSERT(false, "ERROR: " + shaderType + " is unknown shader type!Please specify shader type!");
	}
}
hexen::engine::graphics::ShaderType hexen::engine::graphics::ShaderFile::getType() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return type;
}

//
// Created by cx9ps3 on 03.01.23.
//

#include "ShaderFile.hpp"
#include "../render_context/RenderContext.hpp"
#include "SDL3/SDL.h"

void hexen::engine::graphics::ShaderFile::read(const std::string &path)
{
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


	switch (RenderContext::getRenderAPI())
	{

		case RenderContext::RenderAPI::NO_API:
			HEXEN_ASSERT(false,"ERROR:Failed to load shader,Render API not set!");
			break;
		case RenderContext::RenderAPI::OPENGL_API:

			break;
		case RenderContext::RenderAPI::VULKAN_API:
			break;
		case RenderContext::RenderAPI::DIRECTX12_API:
			break;
	}
}

char *hexen::engine::graphics::ShaderFile::getContent()
{
	return const_cast<char *>(shaderText.c_str());
}
void hexen::engine::graphics::ShaderFile::setShaderType(const std::string &path)
{
	if(RenderContext::getRenderAPI() == RenderContext::RenderAPI::OPENGL_API)
	{
		auto typeToken = "#type";
		auto tokenPosition = shaderText.find(typeToken);
		HEXEN_ASSERT(tokenPosition != std::string::npos,"ERROR: Token #type in shader file " + path + " not found! Please specify shader type!");

	}
}

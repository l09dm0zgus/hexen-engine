//
// Created by cx9ps3 on 28.10.2023.
//
#include "GLTextureArray.hpp"
#include "../profiling/Profiling.hpp"
#include "GLTexture2D.hpp"

#ifndef __ANDROID__
	#include "GL/glew.h"
#else
	#include <GLES3/gl31.h>
#endif

hexen::engine::graphics::gl::GLTextureArray::GLTextureArray(TextureFilter textureFilter, const glm::vec2 &size) : imageSize(size)
{
	HEXEN_ADD_TO_PROFILE();
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0 + textureSlotIndex);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, imageSize.x, imageSize.y, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, textureFilterToGLTextureFilter(textureFilter));
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, textureFilterToGLTextureFilter(textureFilter));
}
//TODO: Load texture from image assets
void hexen::engine::graphics::gl::GLTextureArray::addTextureToArray(const std::string &path)
{
	HEXEN_ADD_TO_PROFILE();
	auto surface = IMG_Load(path.c_str());

	if (surface == nullptr)
	{
		SDL_Log("Error : Failed to load %s image.", path.c_str());
	}

	auto internalFormat = GL_RGB8, dataFormat = GL_RGB;

	if (surface->format->Amask)
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}

	HEXEN_ASSERT(internalFormat & dataFormat, "Format not supported!");

	auto height = surface->h;
	auto width = surface->w;

	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, imageIndex, width, height, 1, dataFormat, GL_UNSIGNED_BYTE, surface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
	imageIndex++;
}

hexen::engine::core::u32 hexen::engine::graphics::gl::GLTextureArray::getWidth() const
{
	HEXEN_ADD_TO_PROFILE();
	return imageSize.x;
}

hexen::engine::core::u32 hexen::engine::graphics::gl::GLTextureArray::getHeight() const
{
	HEXEN_ADD_TO_PROFILE();
	return imageSize.y;
}

void hexen::engine::graphics::gl::GLTextureArray::bind(hexen::engine::core::u32 slot) const
{
	HEXEN_ADD_TO_PROFILE();
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
}

hexen::engine::core::u32 hexen::engine::graphics::gl::GLTextureArray::getId() const
{
	HEXEN_ADD_TO_PROFILE();
	return textureID;
}

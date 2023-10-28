//
// Created by cx9ps3 on 06.01.23.
//

#include "GLTexture2D.hpp"
#include "../profiling/Profiling.hpp"

hexen::engine::graphics::gl::GLTexture2D::~GLTexture2D()
{
	HEXEN_ADD_TO_PROFILE();
	glDeleteTextures(1, &textureId);
}

void hexen::engine::graphics::gl::GLTexture2D::bind(core::u32 slot) const
{
	HEXEN_ADD_TO_PROFILE();
	glBindTextureUnit(slot,textureId);
}

hexen::engine::graphics::gl::GLTexture2D::GLTexture2D(const std::string &pathToImage,TextureFilter filter)
{
	HEXEN_ADD_TO_PROFILE();
	auto surface = IMG_Load(pathToImage.c_str());

	if (surface == nullptr)
	{
		SDL_Log("Error : Failed to load %s image.", pathToImage.c_str());
	}

	auto internalFormat = GL_RGB8, dataFormat = GL_RGB;

	if (surface->format->Amask)
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}

	HEXEN_ASSERT(internalFormat & dataFormat ,"Format not supported!");

	height = surface->h;
	width = surface->w;

	glCreateTextures(GL_TEXTURE_2D,1, &textureId);
	glTextureStorage2D(textureId,1,internalFormat,width,height);

	glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, textureFilterToGLTextureFilter(filter));
	glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, textureFilterToGLTextureFilter(filter));

	glTextureSubImage2D(textureId,0,0,0,width,height,dataFormat,GL_UNSIGNED_BYTE,surface->pixels);
	SDL_DestroySurface(surface);
}

hexen::engine::core::u32 hexen::engine::graphics::gl::GLTexture2D::getId() const
{
	HEXEN_ADD_TO_PROFILE();
	return textureId;
}

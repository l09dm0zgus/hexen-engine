//
// Created by cx9ps3 on 06.01.23.
//

#include "GLTexture2D.hpp"
#include "../profiling/Profiling.hpp"

#ifndef __ANDROID__
	#include "GL/glew.h"
#else
	#include <GLES3/gl31.h>
#endif

namespace hexen::engine::graphics::gl
{
	int textureFilterToGLTextureFilter(TextureFilter textureFilter)
	{
		{
			HEXEN_ADD_TO_PROFILE();
			switch (textureFilter)
			{
				case TextureFilter::LINEAR:
					return GL_LINEAR;
				case TextureFilter::NEAREST:
					return GL_NEAREST;
			}
			return GL_NEAREST;
		}
	}

	std::pair<int,int> imageFormatToGLTextureFormat(ImageAsset::ImageFormat imageFormat)
	{
		std::pair<int,int> result;
		switch (imageFormat)
		{
			case ImageAsset::ImageFormat::RGB8:
				result.first = GL_RGB8;
				result.second = GL_RGB;
				break;
			case ImageAsset::ImageFormat::RGBA8:
				result.first = GL_RGBA8;
				result.second = GL_RGBA;
				break;
			case ImageAsset::ImageFormat::RGB16:
				result.first = GL_RGB16;
				result.second = GL_RGB;
				break;
			case ImageAsset::ImageFormat::RGBA16:
				result.first = GL_RGBA16;
				result.second = GL_RGBA;
				break;
			case ImageAsset::ImageFormat::RGB32:
				result.first = GL_RGB32F;
				result.second = GL_RGB;
				break;
			case ImageAsset::ImageFormat::RGBA32:
				result.first = GL_RGBA32F;
				result.second = GL_RGBA;
				break;
			default:
				result.first = GL_RGB8;
				result.second = GL_RGB;
				break;
		}
		return result;
	}
}
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

hexen::engine::graphics::gl::GLTexture2D::GLTexture2D(const std::shared_ptr<ImageAsset> &imageAsset, TextureFilter filter, bool flipImage)
{
	HEXEN_ADD_TO_PROFILE();

	auto formats = imageFormatToGLTextureFormat(imageAsset->getFormat());

	width = imageAsset->getWidth();
	height = imageAsset->getHeight();

	if(flipImage)
	{
		imageAsset->flip();
	}

	HEXEN_ASSERT(formats.first & formats.second ,"Format not supported!");

	glCreateTextures(GL_TEXTURE_2D,1, &textureId);
	glTextureStorage2D(textureId,1,formats.first,width,height);

	glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, textureFilterToGLTextureFilter(filter));
	glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, textureFilterToGLTextureFilter(filter));

	glTextureSubImage2D(textureId,0,0,0,width,height,formats.second,GL_UNSIGNED_BYTE, imageAsset->getRawData());

}

hexen::engine::core::u32 hexen::engine::graphics::gl::GLTexture2D::getId() const
{
	HEXEN_ADD_TO_PROFILE();
	return textureId;
}

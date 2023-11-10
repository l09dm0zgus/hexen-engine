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
	glActiveTexture(GL_TEXTURE0 + getCountOfTextureUnits());
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, imageSize.x, imageSize.y, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, textureFilterToGLTextureFilter(textureFilter));
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, textureFilterToGLTextureFilter(textureFilter));

	increaseCountOfTextureUnits();
}

void hexen::engine::graphics::gl::GLTextureArray::addTextureToArray(const std::shared_ptr<ImageAsset> &imageAsset)
{
	HEXEN_ADD_TO_PROFILE();
	auto formats = imageFormatToGLTextureFormat(imageAsset->getFormat());

	auto width = imageAsset->getWidth();
	auto height = imageAsset->getHeight();

	HEXEN_ASSERT(formats.first & formats.second ,"Format not supported!");

	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, imageIndex, width, height, 1, formats.second, GL_UNSIGNED_BYTE, imageAsset->getRawData());
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
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
}

hexen::engine::core::u32 hexen::engine::graphics::gl::GLTextureArray::getId() const
{
	HEXEN_ADD_TO_PROFILE();
	return textureID;
}

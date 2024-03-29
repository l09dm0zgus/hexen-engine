//
// Created by cx9ps3 on 08.10.2023.
//

#include "Texture.hpp"
#include "../render_context/RenderContext.hpp"
#if defined(_ENABLE_OPENGL_SUPPORT)
	#include "GL/GLTexture2D.hpp"
	#include "GL/GLTextureArray.hpp"
#endif
#include "../profiling/Profiling.hpp"
#include "ImageAsset.hpp"

std::shared_ptr<hexen::engine::graphics::Texture2D> hexen::engine::graphics::Texture2D::create(const std::shared_ptr<ImageAsset> &imageAsset, TextureFilter filter, bool flipImage)
{
	HEXEN_ADD_TO_PROFILE();
	switch (RenderContext::getRenderAPI())
	{
		case core::Settings::RenderAPI::NO_API:
			HEXEN_ASSERT(false, "ERROR::Failed to create Vertex Buffer.Render API is not set or this PC does not support graphics!");
			break;
		case core::Settings::RenderAPI::OPENGL_API:
			if constexpr (RenderContext::enabledOpengl)
			{
				return core::memory::make_shared<gl::GLTexture2D>(imageAsset, filter, flipImage);
			}
			break;
		case core::Settings::RenderAPI::VULKAN_API:
			break;
		case core::Settings::RenderAPI::DIRECTX12_API:
			break;
	}

	return nullptr;
}

std::shared_ptr<hexen::engine::graphics::TextureArray> hexen::engine::graphics::TextureArray::create(const glm::vec2 &size, hexen::engine::graphics::TextureFilter filter)
{
	HEXEN_ADD_TO_PROFILE();
	switch (RenderContext::getRenderAPI())
	{
		case core::Settings::RenderAPI::NO_API:
			HEXEN_ASSERT(false, "ERROR::Failed to create Vertex Buffer.Render API is not set or this PC does not support graphics!");
			break;
		case core::Settings::RenderAPI::OPENGL_API:
			if constexpr (RenderContext::enabledOpengl)
			{
				return core::memory::make_shared<gl::GLTextureArray>(filter, size);
			}
			break;
		case core::Settings::RenderAPI::VULKAN_API:
			break;
		case core::Settings::RenderAPI::DIRECTX12_API:
			break;
	}

	return nullptr;
}

hexen::engine::core::u32 hexen::engine::graphics::TextureArray::countOfTextureUnits = 0;

hexen::engine::core::u32 hexen::engine::graphics::TextureArray::getCountOfTextureUnits()
{
	return countOfTextureUnits;
}

void hexen::engine::graphics::TextureArray::increaseCountOfTextureUnits()
{
	countOfTextureUnits++;
}

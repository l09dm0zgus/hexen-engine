//
// Created by cx9ps3 on 04.10.2023.
//

#include "RenderContext.hpp"

#if defined(_ENABLE_OPENGL_SUPPORT)
	#include "GL/GLRenderContext.hpp"
#endif

hexen::engine::core::Settings hexen::engine::graphics::RenderContext::settings;

std::shared_ptr<hexen::engine::graphics::RenderContext> hexen::engine::graphics::RenderContext::create()
{
	HEXEN_ADD_TO_PROFILE();
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}

	auto currentApi = settings.getRenderAPI();
	switch (currentApi)
	{
		case core::Settings::RenderAPI::NO_API:
			HEXEN_ASSERT(false,"ERROR::Failed to create render context.Render API is not set or this PC does not support graphics! ");
			break;
		case core::Settings::RenderAPI::OPENGL_API:
			if constexpr(enabledOpengl)
			{
				return core::memory::make_shared<gl::GLRenderContext>(settings);
			}
			break;
		case core::Settings::RenderAPI::VULKAN_API:
			break;
		case core::Settings::RenderAPI::DIRECTX12_API:
			break;
	}
	return nullptr;
}
hexen::engine::core::Settings::RenderAPI hexen::engine::graphics::RenderContext::getRenderAPI()
{
	HEXEN_ADD_TO_PROFILE();
	return settings.getRenderAPI();
}


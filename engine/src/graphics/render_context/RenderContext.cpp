//
// Created by cx9ps3 on 04.10.2023.
//

#include "RenderContext.hpp"

#include <application/Settings.hpp>

#if defined(_ENABLE_OPENGL_SUPPORT)
	#include "GL/GLRenderContext.hpp"
#endif

hexen::engine::graphics::RenderContext::RenderAPI hexen::engine::graphics::RenderContext::currentApi = hexen::engine::graphics::RenderContext::RenderAPI::NO_API;


std::unique_ptr<hexen::engine::graphics::RenderContext> hexen::engine::graphics::RenderContext::create(const core::Settings &settings)
{
	currentApi = static_cast<RenderAPI>(settings.getRenderAPI());
	switch (currentApi)
	{
		case RenderAPI::NO_API:
			HEXEN_ASSERT(false,"ERROR::Failed to create render context.Render API is not set or this PC does not support graphics! ");
		case RenderAPI::OPENGL_API:
			if constexpr(enabledOpengl)
			{
				return core::memory::make_unique<gl::GLRenderContext>(settings);
			}

		case RenderAPI::VULKAN_API:
			break;
		case RenderAPI::DIRECTX12_API:
			break;
	}
	return nullptr;
}
hexen::engine::graphics::RenderContext::RenderAPI hexen::engine::graphics::RenderContext::getRenderAPI()
{
	return currentApi;
}
hexen::engine::core::i32 hexen::engine::graphics::RenderContext::getWindowFlags() const noexcept
{
	return 0;
}
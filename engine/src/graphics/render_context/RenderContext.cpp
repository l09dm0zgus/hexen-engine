//
// Created by cx9ps3 on 04.10.2023.
//

#include "RenderContext.hpp"
#include <application/Settings.hpp>

#if defined(_ENABLE_OPENGL_SUPPORT)
	#include "GL/GLRenderContext.hpp"
#endif

std::unique_ptr<hexen::engine::graphics::RenderContext> hexen::engine::graphics::RenderContext::create(const hexen::engine::core::Settings &settings)
{
	currenApi = static_cast<RenderAPI>(settings.getRenderAPI());
	switch (currenApi)
	{
		case RenderAPI::OPENGL_API:
			if constexpr(enabledOpengl)
			{
				return core::memory::make_unique<gl::GLRenderContext>(settings);
			}

		case RenderAPI::NO_API:
			break;
		case RenderAPI::VULKAN_API:
			break;
		case RenderAPI::DIRECTX12_API:
			break;
	}
	return nullptr;
}
hexen::engine::graphics::RenderContext::RenderAPI hexen::engine::graphics::RenderContext::getRenderAPI()
{
	return currenApi;
}
hexen::engine::core::i32 hexen::engine::graphics::RenderContext::getWindowFlags() const noexcept
{
	return 0;
}
//
// Created by cx9ps3 on 04.10.2023.
//

#include "RenderContext.hpp"

#if defined(_ENABLE_OPENGL_SUPPORT)
	#include "GL/GLRenderContext.hpp"
#endif

hexen::engine::core::Settings hexen::engine::graphics::RenderContext::settings;

std::unique_ptr<hexen::engine::graphics::RenderContext> hexen::engine::graphics::RenderContext::create()
{
	auto currentApi = settings.getRenderAPI();
	switch (currentApi)
	{
		case core::Settings::RenderAPI::NO_API:
			HEXEN_ASSERT(false,"ERROR::Failed to create render context.Render API is not set or this PC does not support graphics! ");
			break;
		case core::Settings::RenderAPI::OPENGL_API:
			if constexpr(enabledOpengl)
			{
				return core::memory::make_unique<gl::GLRenderContext>(settings);
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
	return settings.getRenderAPI();
}
hexen::engine::core::i32 hexen::engine::graphics::RenderContext::getWindowFlags() const noexcept
{
	return 0;
}

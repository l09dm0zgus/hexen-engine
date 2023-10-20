//
// Created by cx9ps3 on 07.10.2023.
//

#include "VertexArray.hpp"
#if defined(_ENABLE_OPENGL_SUPPORT)
	#include "GL/GLVertexArray.hpp"
#endif
#include "../render_context/RenderContext.hpp"
#include "../profiling/Profiling.hpp"

std::unique_ptr<hexen::engine::graphics::VertexArray> hexen::engine::graphics::VertexArray::create()
{
	HEXEN_ADD_TO_PROFILE();
	switch (RenderContext::getRenderAPI())
	{
		case core::Settings::RenderAPI::NO_API:
			HEXEN_ASSERT(false,"ERROR::Failed to create Element Buffer.Render API is not set or this PC does not support graphics!");
			break;
		case core::Settings::RenderAPI::OPENGL_API:
			if constexpr (RenderContext::enabledOpengl)
			{
				return core::memory::make_unique<gl::GLVertexArray>();
			}
			break;
		case core::Settings::RenderAPI::VULKAN_API:
			break;
		case core::Settings::RenderAPI::DIRECTX12_API:
			break;
	}
	return nullptr;
}

//
// Created by cx9ps3 on 06.10.2023.
//
#include "Buffers.hpp"
#include "../render_context/RenderContext.hpp"

#if defined(_ENABLE_OPENGL_SUPPORT)
	#include "GL/GLElementsBuffer.hpp"
#endif

std::unique_ptr<hexen::engine::graphics::ElementsBuffer> hexen::engine::graphics::ElementsBuffer::create(hexen::engine::core::u32 *indices, hexen::engine::core::u32 size)
{
	switch (RenderContext::getRenderAPI())
	{
		case RenderContext::RenderAPI::NO_API:
			HEXEN_ASSERT(false,"ERROR::Failed to create Element Buffer.Render API is not set or this PC does not support graphics!");
			break;
		case RenderContext::RenderAPI::OPENGL_API:
			return core::memory::make_unique<gl::GLElementsBuffer>(indices, size);
			break;
		case RenderContext::RenderAPI::VULKAN_API:
			break;
		case RenderContext::RenderAPI::DIRECTX12_API:
			break;
	}
	return nullptr;
}

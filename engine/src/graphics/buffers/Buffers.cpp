//
// Created by cx9ps3 on 06.10.2023.
//
#include "Buffers.hpp"
#include "../render_context/RenderContext.hpp"

#if defined(_ENABLE_OPENGL_SUPPORT)
	#include "GL/GLElementsBuffer.hpp"
	#include "GL/GLVertexBuffer.hpp"
	#include "GL/GLFrameBuffer.hpp"
#endif

std::unique_ptr<hexen::engine::graphics::ElementsBuffer> hexen::engine::graphics::ElementsBuffer::create(hexen::engine::core::u32 *indices, hexen::engine::core::u32 size)
{
	switch (RenderContext::getRenderAPI())
	{
		case RenderContext::RenderAPI::NO_API:
			HEXEN_ASSERT(false,"ERROR::Failed to create Element Buffer.Render API is not set or this PC does not support graphics!");
			break;
		case RenderContext::RenderAPI::OPENGL_API:
			if constexpr (RenderContext::enabledOpengl)
			{
				return core::memory::make_unique<gl::GLElementsBuffer>(indices, size);
			}
			break;
		case RenderContext::RenderAPI::VULKAN_API:
			break;
		case RenderContext::RenderAPI::DIRECTX12_API:
			break;
	}
	return nullptr;
}
std::unique_ptr<hexen::engine::graphics::VertexBuffer> hexen::engine::graphics::VertexBuffer::create(float *vertices, hexen::engine::core::u32 size)
{
	switch (RenderContext::getRenderAPI())
	{
		case RenderContext::RenderAPI::NO_API:
			HEXEN_ASSERT(false,"ERROR::Failed to create Vertex Buffer.Render API is not set or this PC does not support graphics!");
			break;
		case RenderContext::RenderAPI::OPENGL_API:
			if constexpr (RenderContext::enabledOpengl)
			{
				return core::memory::make_unique<gl::GLVertexBuffer>(vertices, size);
			}
			break;
		case RenderContext::RenderAPI::VULKAN_API:
			break;
		case RenderContext::RenderAPI::DIRECTX12_API:
			break;
	}

	return nullptr;
}
std::unique_ptr<hexen::engine::graphics::FrameBuffer> hexen::engine::graphics::FrameBuffer::create(const glm::vec2 &size)
{
	switch (RenderContext::getRenderAPI())
	{
		case RenderContext::RenderAPI::NO_API:
			HEXEN_ASSERT(false,"ERROR::Failed to create Frame Buffer.Render API is not set or this PC does not support graphics!");
			break;
		case RenderContext::RenderAPI::OPENGL_API:
			if constexpr (RenderContext::enabledOpengl)
			{
				return core::memory::make_unique<gl::GLFrameBuffer>(size);
			}
			break;
		case RenderContext::RenderAPI::VULKAN_API:
			break;
		case RenderContext::RenderAPI::DIRECTX12_API:
			break;
	}

	return nullptr;
}

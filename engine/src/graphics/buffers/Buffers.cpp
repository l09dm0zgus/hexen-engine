//
// Created by cx9ps3 on 06.10.2023.
//
#include "Buffers.hpp"
#include "../render_context/RenderContext.hpp"

#if defined(_ENABLE_OPENGL_SUPPORT)
	#include "GL/GLElementsBuffer.hpp"
	#include "GL/GLVertexBuffer.hpp"
	#include "GL/GLFrameBuffer.hpp"
	#include "GL/GlUniformBuffer.hpp"
#endif

std::shared_ptr<hexen::engine::graphics::ElementsBuffer> hexen::engine::graphics::ElementsBuffer::create(hexen::engine::core::u32 *indices, hexen::engine::core::u32 size)
{
	HEXEN_ADD_TO_PROFILE();
	switch (RenderContext::getRenderAPI())
	{
		case core::Settings::RenderAPI::NO_API:
			HEXEN_ASSERT(false, "ERROR::Failed to create Element Buffer.Render API is not set or this PC does not support graphics!");
			break;
		case core::Settings::RenderAPI::OPENGL_API:
			if constexpr (RenderContext::enabledOpengl)
			{
				return core::memory::make_shared<gl::GLElementsBuffer>(indices, size);
			}
			break;
		case core::Settings::RenderAPI::VULKAN_API:
			break;
		case core::Settings::RenderAPI::DIRECTX12_API:
			break;
	}
	return nullptr;
}

std::shared_ptr<hexen::engine::graphics::ElementsBuffer> hexen::engine::graphics::ElementsBuffer::create(core::u32 size)
{
	HEXEN_ADD_TO_PROFILE();
	switch (RenderContext::getRenderAPI())
	{
		case core::Settings::RenderAPI::NO_API:
			HEXEN_ASSERT(false, "ERROR::Failed to create Element Buffer.Render API is not set or this PC does not support graphics!");
		break;
		case core::Settings::RenderAPI::OPENGL_API:
			if constexpr (RenderContext::enabledOpengl)
			{
				return core::memory::make_shared<gl::GLElementsBuffer>(size);
			}
		break;
		case core::Settings::RenderAPI::VULKAN_API:
			break;
		case core::Settings::RenderAPI::DIRECTX12_API:
			break;
	}
	return nullptr;
}

std::shared_ptr<hexen::engine::graphics::VertexBuffer> hexen::engine::graphics::VertexBuffer::create(float *vertices, hexen::engine::core::u32 size)
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
				return core::memory::make_shared<gl::GLVertexBuffer>(vertices, size);
			}
			break;
		case core::Settings::RenderAPI::VULKAN_API:
			break;
		case core::Settings::RenderAPI::DIRECTX12_API:
			break;
	}

	return nullptr;
}

std::shared_ptr<hexen::engine::graphics::VertexBuffer> hexen::engine::graphics::VertexBuffer::create(hexen::engine::core::u32 size)
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
				return core::memory::make_shared<gl::GLVertexBuffer>(size);
			}
			break;
		case core::Settings::RenderAPI::VULKAN_API:
			break;
		case core::Settings::RenderAPI::DIRECTX12_API:
			break;
	}

	return nullptr;
}

std::shared_ptr<hexen::engine::graphics::FrameBuffer> hexen::engine::graphics::FrameBuffer::create(const FrameBufferSpecification &specification)
{
	HEXEN_ADD_TO_PROFILE();
	switch (RenderContext::getRenderAPI())
	{
		case core::Settings::RenderAPI::NO_API:
			HEXEN_ASSERT(false, "ERROR::Failed to create Frame Buffer.Render API is not set or this PC does not support graphics!");
			break;
		case core::Settings::RenderAPI::OPENGL_API:
			if constexpr (RenderContext::enabledOpengl)
			{
				return core::memory::make_unique<gl::GLFrameBuffer>(specification);
			}
			break;
		case core::Settings::RenderAPI::VULKAN_API:
			break;
		case core::Settings::RenderAPI::DIRECTX12_API:
			break;
	}

	return nullptr;
}

hexen::engine::graphics::BufferElement::BufferElement(ShaderDataType newType, const std::string &newName, bool isNormalized) : name(newName), type(newType), size(getShaderDataTypeSize(newType)), offset(0), bIsNormalized(isNormalized)
{
	HEXEN_ADD_TO_PROFILE();
}

hexen::engine::core::u32 hexen::engine::graphics::BufferElement::getComponentCount() const
{
	HEXEN_ADD_TO_PROFILE();
	switch (type)
	{
		case ShaderDataType::FLOAT:
			return 1;
		case ShaderDataType::INT:
			return 1;
		case ShaderDataType::VEC2F:
			return 2;
		case ShaderDataType::VEC3F:
			return 3;
		case ShaderDataType::VEC4F:
			return 4;
		case ShaderDataType::VEC2I:
			return 2;
		case ShaderDataType::VEC3I:
			return 3;
		case ShaderDataType::VEC4I:
			return 4;
		case ShaderDataType::MAT2:
			return 2 * 2;
		case ShaderDataType::MAT3:
			return 3 * 3;
		case ShaderDataType::MAT4:
			return 4 * 4;
		case ShaderDataType::BOOL:
			return 1;
		case ShaderDataType::NONE:
			return 0;
	}

	HEXEN_ASSERT(false, "ERROR::Unknown ShaderDataType!");
	return 0;
}

hexen::engine::core::u32 hexen::engine::graphics::getShaderDataTypeSize(hexen::engine::graphics::ShaderDataType type)
{
	HEXEN_ADD_TO_PROFILE();
	switch (type)
	{
		case ShaderDataType::FLOAT:
			return 4;
		case ShaderDataType::INT:
			return 4;
		case ShaderDataType::VEC2F:
			return 4 * 2;
		case ShaderDataType::VEC3F:
			return 4 * 3;
		case ShaderDataType::VEC4F:
			return 4 * 4;
		case ShaderDataType::VEC2I:
			return 4 * 2;
		case ShaderDataType::VEC3I:
			return 4 * 3;
		case ShaderDataType::VEC4I:
			return 4 * 4;
		case ShaderDataType::MAT2:
			return 4 * 2 * 2;
		case ShaderDataType::MAT3:
			return 4 * 3 * 3;
		case ShaderDataType::MAT4:
			return 4 * 4 * 4;
		case ShaderDataType::BOOL:
			return 1;
		case ShaderDataType::NONE:
			return 0;
	}

	HEXEN_ASSERT(false, "ERROR::Unknown ShaderDataType!");
	return 0;
}

void hexen::engine::graphics::BufferLayout::calculateStridesAndOffsets()
{
	HEXEN_ADD_TO_PROFILE();
	core::u32 offset = 0;
	stride = 0;

	for (auto &element : elements)
	{
		element.offset = offset;
		offset += element.size;
		stride += element.size;
	}
}

hexen::engine::graphics::BufferLayout::BufferLayout(const std::initializer_list<BufferElement> &newElements) : elements(newElements)
{
	HEXEN_ADD_TO_PROFILE();
	calculateStridesAndOffsets();
}

std::shared_ptr<hexen::engine::graphics::UniformBuffer> hexen::engine::graphics::UniformBuffer::create(hexen::engine::core::u32 size, hexen::engine::core::u32 binding)
{
	HEXEN_ADD_TO_PROFILE();
	switch (RenderContext::getRenderAPI())
	{
		case core::Settings::RenderAPI::NO_API:
			HEXEN_ASSERT(false, "ERROR::Failed to create Uniform Buffer.Render API is not set or this PC does not support graphics!");
			break;
		case core::Settings::RenderAPI::OPENGL_API:
			if constexpr (RenderContext::enabledOpengl)
			{
				return core::memory::make_shared<gl::GLUniformBuffer>(size, binding);
			}
			break;
		case core::Settings::RenderAPI::VULKAN_API:
			break;
		case core::Settings::RenderAPI::DIRECTX12_API:
			break;
	}
	return nullptr;
}

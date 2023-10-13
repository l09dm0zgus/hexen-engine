//
// Created by cx9ps3 on 09.10.2023.
//

#include "ShaderProgram.hpp"
#include "../render_context/RenderContext.hpp"
#if defined(_ENABLE_OPENGL_SUPPORT)
	#include "GL/GLShaderProgram.hpp"
#endif


std::shared_ptr<hexen::engine::graphics::ShaderProgram> hexen::engine::graphics::ShaderProgram::create(std::vector<std::string> &pathsToShaders)
{
	switch (RenderContext::getRenderAPI())
	{
		case RenderContext::RenderAPI::NO_API:
			HEXEN_ASSERT(false,"ERROR::Failed to create Frame Buffer.Render API is not set or this PC does not support graphics!");
			break;
		case RenderContext::RenderAPI::OPENGL_API:
			if constexpr (RenderContext::enabledOpengl)
			{
				return core::memory::make_shared<gl::GLShaderProgram>(pathsToShaders);
			}
			break;
		case RenderContext::RenderAPI::VULKAN_API:
			break;
		case RenderContext::RenderAPI::DIRECTX12_API:
			break;
	}

	return nullptr;;
}

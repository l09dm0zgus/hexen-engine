//
// Created by cx9ps3 on 09.10.2023.
//

#include "ShaderProgram.hpp"
#include "../render_context/RenderContext.hpp"
#if defined(_ENABLE_OPENGL_SUPPORT)
	#include "GL/GLShaderProgram.hpp"

#endif
#include "../profiling/Profiling.hpp"

std::shared_ptr<hexen::engine::graphics::ShaderProgram> hexen::engine::graphics::ShaderProgram::create(const std::vector<std::string> &pathsToShaders)
{
	HEXEN_ADD_TO_PROFILE();
	switch (RenderContext::getRenderAPI())
	{
		case core::Settings::RenderAPI::NO_API:
			HEXEN_ASSERT(false,"ERROR::Failed to create Frame Buffer.Render API is not set or this PC does not support graphics!");
			break;
		case core::Settings::RenderAPI::OPENGL_API:
			if constexpr (RenderContext::enabledOpengl)
			{
				return core::memory::make_shared<gl::GLShaderProgram>(pathsToShaders);
			}
			break;
		case core::Settings::RenderAPI::VULKAN_API:
			break;
		case core::Settings::RenderAPI::DIRECTX12_API:
			break;
	}

	return nullptr;;
}

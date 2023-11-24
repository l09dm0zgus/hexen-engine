//
// Created by cx9ps3 on 24.11.2023.
//

#include "EnableBlendingCommand.hpp"

#include "../render_context/RenderContext.hpp"

#if defined(_ENABLE_OPENGL_SUPPORT)
	#include "GL_subcommands/GLEnableBlending.hpp"
#endif

#include "../profiling/Profiling.hpp"

void hexen::engine::graphics::EnableBlendingCommand::execute()
{
	HEXEN_ADD_TO_PROFILE();
	switch(RenderContext::getRenderAPI())
	{
		case core::Settings::RenderAPI::NO_API:
			break;
		case core::Settings::RenderAPI::OPENGL_API:
			gl::enableBlending();
			break;
		case core::Settings::RenderAPI::VULKAN_API:
			break;
		case core::Settings::RenderAPI::DIRECTX12_API:
			break;
	}
}

void hexen::engine::graphics::EnableBlendingCommand::prepare()
{
}

void hexen::engine::graphics::EnableBlendingCommand::finish()
{
}

hexen::engine::graphics::EnableBlendingCommand::EnableBlendingCommand()
{
	HEXEN_ADD_TO_PROFILE();
	// used for optimization , see IRenderCommand and RenderPipeline class for details.
	enableExecute = false;
	enableFinish = false;
	enablePrepare = true;
}

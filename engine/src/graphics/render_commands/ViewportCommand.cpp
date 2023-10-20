//
// Created by cx9ps3 on 16.10.2023.
//

#include "ViewportCommand.hpp"
#if defined(_ENABLE_OPENGL_SUPPORT)
	#include "GL_subcommands/GLViewport.hpp"
#endif


hexen::engine::graphics::ViewportCommand::ViewportCommand(const glm::ivec4 &params) : parameters(params)
{
	// used for optimization , see IRenderCommand and RenderPipeline class for details.
	enableExecute = false;
	enableFinish = true;
	enablePrepare = false;
}

void hexen::engine::graphics::ViewportCommand::execute()
{
	HEXEN_ADD_TO_PROFILE();
	switch(RenderContext::getRenderAPI())
	{
		case core::Settings::RenderAPI::NO_API:
			break;
		case core::Settings::RenderAPI::OPENGL_API:
			gl::viewport(parameters);
			break;
		case core::Settings::RenderAPI::VULKAN_API:
			break;
		case core::Settings::RenderAPI::DIRECTX12_API:
			break;
	}
}

void hexen::engine::graphics::ViewportCommand::prepare()
{

}

void hexen::engine::graphics::ViewportCommand::finish()
{

}

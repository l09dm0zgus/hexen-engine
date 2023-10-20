//
// Created by cx9ps3 on 15.10.2023.
//

#include "ClearCommand.hpp"
#include "../render_context/RenderContext.hpp"

#if defined(_ENABLE_OPENGL_SUPPORT)
	#include "GL_subcommands/GLClear.hpp"
#endif

#include "../profiling/Profiling.hpp"

hexen::engine::graphics::ClearCommand::ClearCommand(const glm::vec4& color) : color(color)
{
	HEXEN_ADD_TO_PROFILE();
	// used for optimization , see IRenderCommand and RenderPipeline class for details.
	enableExecute = false;
	enableFinish = false;
	enablePrepare = true;
}
void hexen::engine::graphics::ClearCommand::execute()
{
	HEXEN_ADD_TO_PROFILE();
	switch(RenderContext::getRenderAPI())
	{
		case core::Settings::RenderAPI::NO_API:
			break;
		case core::Settings::RenderAPI::OPENGL_API:
			gl::clear(color);
			break;
		case core::Settings::RenderAPI::VULKAN_API:
			break;
		case core::Settings::RenderAPI::DIRECTX12_API:
			break;
	}
}
void hexen::engine::graphics::ClearCommand::prepare()
{

}
void hexen::engine::graphics::ClearCommand::finish()
{
}

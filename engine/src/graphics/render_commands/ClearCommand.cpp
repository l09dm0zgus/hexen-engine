//
// Created by cx9ps3 on 15.10.2023.
//

#include "ClearCommand.hpp"
#include "../render_context/RenderContext.hpp"

#if defined(_ENABLE_OPENGL_SUPPORT)
	#include "GL_subcommands/GLClear.hpp"
#endif

hexen::engine::graphics::ClearCommand::ClearCommand(const glm::vec4& color) : color(color)
{
	// used for optimization , see IRenderCommand and RenderPipeline class for details.
	enableExecute = false;
	enableFinish = false;
	enablePrepare = true;
}
void hexen::engine::graphics::ClearCommand::execute()
{

}
void hexen::engine::graphics::ClearCommand::prepare()
{
	switch(RenderContext::getRenderAPI())
	{
		case RenderContext::RenderAPI::NO_API:
			break;
		case RenderContext::RenderAPI::OPENGL_API:
			clear(color);
			break;
		case RenderContext::RenderAPI::VULKAN_API:
			break;
		case RenderContext::RenderAPI::DIRECTX12_API:
			break;
	}
}
void hexen::engine::graphics::ClearCommand::finish()
{
}

//
// Created by cx9ps3 on 13.10.2023.
//

#include "FramebufferCommand.hpp"
hexen::engine::graphics::FramebufferCommand::FramebufferCommand(const hexen::engine::graphics::FrameBufferSpecification &specification)
{
	frameBuffer = FrameBuffer::create(specification);

	// used for optimization , see IRenderCommand and RenderPipeline class for details.
	enableExecute = false;
	enableFinish = true;
	enablePrepare = true;
}
void hexen::engine::graphics::FramebufferCommand::prepare()
{
	frameBuffer->bind();
}
void hexen::engine::graphics::FramebufferCommand::finish()
{
	frameBuffer->unbind();
}
void hexen::engine::graphics::FramebufferCommand::execute()
{
}
hexen::engine::core::u32 hexen::engine::graphics::FramebufferCommand::getColorAttachment() const noexcept
{
	return frameBuffer->getColorAttachmentObject();
}

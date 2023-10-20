//
// Created by cx9ps3 on 13.10.2023.
//

#include "FramebufferCommand.hpp"
hexen::engine::graphics::FramebufferCommand::FramebufferCommand(const hexen::engine::graphics::FrameBufferSpecification &specification)
{
	HEXEN_ADD_TO_PROFILE();
	frameBuffer = FrameBuffer::create(specification);

	// used for optimization , see IRenderCommand and RenderPipeline class for details.
	enableExecute = false;
	enableFinish = true;
	enablePrepare = true;
}

void hexen::engine::graphics::FramebufferCommand::prepare()
{
	HEXEN_ADD_TO_PROFILE();
	frameBuffer->bind();
}

void hexen::engine::graphics::FramebufferCommand::finish()
{
	HEXEN_ADD_TO_PROFILE();
	frameBuffer->unbind();
}

void hexen::engine::graphics::FramebufferCommand::execute()
{
}

hexen::engine::core::u32 hexen::engine::graphics::FramebufferCommand::getColorAttachment() const noexcept
{
	HEXEN_ADD_TO_PROFILE();
	return frameBuffer->getColorAttachmentObject();
}

std::shared_ptr<hexen::engine::graphics::FrameBuffer> hexen::engine::graphics::FramebufferCommand::getPointerToFrameBuffer() const
{
	HEXEN_ADD_TO_PROFILE();
	return frameBuffer;
}

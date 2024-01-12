//
// Created by cx9ps3 on 13.10.2023.
//

#include "RenderPipeline.hpp"
phmap::parallel_flat_hash_map<hexen::engine::graphics::RenderPipelineID, std::shared_ptr<hexen::engine::graphics::RenderPipeline>> hexen::engine::graphics::RenderPipeline::renderPipelines;
hexen::engine::core::u8 hexen::engine::graphics::RenderPipeline::countOfRenderPipelines = 0;

std::shared_ptr<hexen::engine::graphics::IRenderCommand> hexen::engine::graphics::RenderPipeline::getCommand(hexen::engine::core::u32 commandID)
{
	HEXEN_ADD_TO_PROFILE();
	return renderQueue[commandID];
}
void hexen::engine::graphics::RenderPipeline::removeCommandFromQueue(hexen::engine::core::u32 commandId)
{
	HEXEN_ADD_TO_PROFILE();
	renderQueue.erase(renderQueue.cbegin() + commandId);
}
void hexen::engine::graphics::RenderPipeline::executeCommands()
{
	HEXEN_ADD_TO_PROFILE();
	for (const auto &command : renderQueue)
	{
		if (command->enableExecute)
		{
			command->execute();
		}
	}
}
void hexen::engine::graphics::RenderPipeline::prepareCommands()
{
	HEXEN_ADD_TO_PROFILE();
	for (const auto &command : renderQueue)
	{
		if (command->enablePrepare)
		{
			command->prepare();
		}
	}
}
void hexen::engine::graphics::RenderPipeline::finishCommands()
{
	HEXEN_ADD_TO_PROFILE();
	for (const auto &command : renderQueue)
	{
		if (command->enableFinish)
		{
			command->finish();
		}
	}
}

void hexen::engine::graphics::RenderPipeline::cacheNextRenderCommand()
{
	cacheCommand = true;
}

std::shared_ptr<hexen::engine::graphics::RenderPipeline> hexen::engine::graphics::RenderPipeline::create()
{
	auto id = static_cast<RenderPipelineID>(countOfRenderPipelines);
	auto renderPipeline = core::memory::make_shared<RenderPipeline>(id);
	renderPipelines[id] = renderPipeline;
	countOfRenderPipelines++;
	return renderPipeline;
}

void hexen::engine::graphics::RenderPipeline::cacheNextRenderCommand(hexen::engine::graphics::RenderPipelineID renderPipelineId)
{
	getRenderPipelineByID(renderPipelineId)->cacheNextRenderCommand();
}

std::shared_ptr<hexen::engine::graphics::RenderPipeline> hexen::engine::graphics::RenderPipeline::getRenderPipelineByID(hexen::engine::graphics::RenderPipelineID id)
{
	return renderPipelines[id];
}

std::shared_ptr<hexen::engine::graphics::IRenderCommand> hexen::engine::graphics::RenderPipeline::getCommand(hexen::engine::graphics::RenderPipelineID renderPipelineId, hexen::engine::core::u32 commandID)
{
	return getRenderPipelineByID(renderPipelineId)->getCommand(commandID);
}

void hexen::engine::graphics::RenderPipeline::removeCommandFromQueue(hexen::engine::graphics::RenderPipelineID renderPipelineId, hexen::engine::core::u32 commandId)
{
	getRenderPipelineByID(renderPipelineId)->removeCommandFromQueue(commandId);
}

hexen::engine::graphics::RenderPipeline::RenderPipeline(hexen::engine::graphics::RenderPipelineID id) : id(id)
{
}

hexen::engine::graphics::RenderPipelineID hexen::engine::graphics::RenderPipeline::getID() const noexcept
{
	return id;
}

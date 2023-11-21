//
// Created by cx9ps3 on 13.10.2023.
//

#include "RenderPipeline.hpp"
hexen::engine::core::u32 hexen::engine::graphics::RenderPipeline::ids = 0;
phmap::parallel_flat_hash_map<hexen::engine::core::u32,std::shared_ptr<hexen::engine::graphics::IRenderCommand>> hexen::engine::graphics::RenderPipeline::renderQueue;
phmap::parallel_flat_hash_map<std::string, std::shared_ptr<hexen::engine::graphics::IRenderCommand>> hexen::engine::graphics::RenderPipeline::cachedRenderCommands;
bool hexen::engine::graphics::RenderPipeline::cacheCommand = false;

std::shared_ptr<hexen::engine::graphics::IRenderCommand> hexen::engine::graphics::RenderPipeline::getCommand(hexen::engine::core::u32 commandID)
{
	HEXEN_ADD_TO_PROFILE();
	return renderQueue[commandID];
}
void hexen::engine::graphics::RenderPipeline::removeCommandFromQueue(hexen::engine::core::u32 commandId)
{
	HEXEN_ADD_TO_PROFILE();
	renderQueue.erase(commandId);
}
void hexen::engine::graphics::RenderPipeline::executeCommands()
{
	HEXEN_ADD_TO_PROFILE();
	for(const auto &command : renderQueue)
	{
		if(command.second->enableExecute)
		{
			command.second->execute();
		}
	}
}
void hexen::engine::graphics::RenderPipeline::prepareCommands()
{
	HEXEN_ADD_TO_PROFILE();
	for(const auto &command : renderQueue)
	{
		if(command.second->enablePrepare)
		{
			command.second->prepare();
		}
	}
}
void hexen::engine::graphics::RenderPipeline::finishCommands()
{
	HEXEN_ADD_TO_PROFILE();
	for(const auto &command : renderQueue)
	{
		if(command.second->enableFinish)
		{
			command.second->finish();
		}
	}
}

void hexen::engine::graphics::RenderPipeline::cacheNextRenderCommand()
{
	cacheCommand = true;
}

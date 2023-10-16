//
// Created by cx9ps3 on 29.07.2023.
//

#include "GameLoop.hpp"
#include "RenderSystem.hpp"
#include "TaskSystem.hpp"
#include "window/Window.hpp"
#include <chrono>
#include <render_commands/ClearCommand.hpp>


void hexen::engine::systems::GameLoop::start()
{
	systems::SystemsManager::addRenderSystem<systems::RenderSystem>(100);
	systemManager->start();

}

void hexen::engine::systems::GameLoop::loop()
{
	initializeClock();

	while (window->isOpen())
	{
		setFrameStart();
		setAccumulator();

		//process input
		systemManager->processInput(window);

		while (accumulator > deltaTime)
		{
			//update
			systemManager->update(deltaTime);
			accumulator -= deltaTime;
		}

		graphics::RenderPipeline::prepareCommands();
		graphics::RenderPipeline::executeCommandNow<graphics::ClearCommand>(glm::vec4(0.39f, 0.58f, 0.93f, 1.f));
		systemManager->render(getAlpha());
		graphics::RenderPipeline::finishCommands();
		window->swapBuffers();
		systems::TaskSystem::waitForCounter();
	}
}


void hexen::engine::systems::GameLoop::initializeClock()
{
	framesStart = std::chrono::steady_clock::now();
}


void hexen::engine::systems::GameLoop::setFrameStart()
{
	auto currentTime = std::chrono::steady_clock::now();

	accumulator += (currentTime - framesStart).count();

	framesStart = currentTime;
}


void hexen::engine::systems::GameLoop::setAccumulator()
{
	if (accumulator > msPerUpdate)
	{
		accumulator = msPerUpdate;
	}
}

double hexen::engine::systems::GameLoop::getAlpha()
{
	return accumulator / deltaTime;
}

hexen::engine::systems::GameLoop::GameLoop(const std::shared_ptr<core::Window> &newWindow)
{
	//initialize thread and fiber pool
	systems::TaskSystem::initialize();

	systemManager = core::memory::make_shared<systems::SystemsManager>();

	HEXEN_ASSERT(systemManager != nullptr, "System manager is nullptr!");

	systems::SystemsManager::setCurrentSystemManager(systemManager.get());
	window = newWindow;


}

hexen::engine::systems::GameLoop::~GameLoop()
{
	systems::SystemsManager::setCurrentSystemManager(nullptr);
}

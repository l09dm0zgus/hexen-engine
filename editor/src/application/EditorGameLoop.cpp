//
// Created by cx9ps3 on 01.08.2023.
//

#include "EditorGameLoop.hpp"
#include "../gui/EditorGUI.hpp"
#include "../systems/EditorSystemsManager.hpp"
#include "core/window/Window.hpp"
#include "entity/scene/SceneManager.hpp"
#include <profiling/Profiling.h>
#include <systems/TaskSystem.hpp>
#include <graphics/render_commands/RenderPipeline.hpp>
#include <graphics/render_commands/ClearCommand.hpp>

hexen::editor::EditorGameLoop::EditorGameLoop(const std::shared_ptr<hexen::engine::core::Window> &newWindow, const std::shared_ptr<hexen::engine::graphics::RenderContext> &renderContext) : GameLoop(newWindow)
{
	systemManager = hexen::engine::core::memory::make_shared<hexen::editor::systems::EditorSystemsManager>();

	HEXEN_ASSERT(systemManager != nullptr, "System manager is nullptr!");

	systems::EditorSystemsManager::setCurrentSystemManager(systemManager.get());

	editorGui = engine::core::memory::make_shared<gui::EditorGUI>(window , renderContext);
}

hexen::editor::EditorGameLoop::~EditorGameLoop()
{
	systems::EditorSystemsManager::setCurrentSystemManager(nullptr);
}


void hexen::editor::EditorGameLoop::start()
{
	ADD_FUNCTION_TO_PROFILING
	auto manager = std::dynamic_pointer_cast<systems::EditorSystemsManager>(systemManager);

	HEXEN_ASSERT(manager != nullptr, "Failed cast to EditorSystemsManager!");

	manager->setEditorGUI(editorGui);

	GameLoop::start();
}


void hexen::editor::EditorGameLoop::loop()
{
	ADD_FUNCTION_TO_PROFILING
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

		if (engine::core::SceneManager::getCurrentScene() != nullptr)
		{
			auto manager = std::dynamic_pointer_cast<systems::EditorSystemsManager>(systemManager);

			HEXEN_ASSERT(manager != nullptr, "Failed cast pointer to EditorSystemsManager");

			manager->addDebugGrid();
		}

		engine::graphics::RenderPipeline::prepareCommands();
		editorGui->renderFrameBufferWindowsContents();
		systemManager->render(getAlpha());
		engine::graphics::RenderPipeline::executeCommands();
		engine::graphics::RenderPipeline::finishCommands();


		editorGui->begin();
		editorGui->draw();
		editorGui->end();

		window->swapBuffers();
		engine::systems::TaskSystem::waitForCounter();
		END_FRAME
	}
}

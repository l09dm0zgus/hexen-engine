//
// Created by cx9ps3 on 01.08.2023.
//

#include "EditorGameLoop.hpp"
#include "../gui/EditorGUI.hpp"
#include "../systems/EditorSystemsManager.hpp"
#include "core/window/Window.hpp"
#include "profiling/Profiling.hpp"
#include <threading/TaskSystem.hpp>
#include <graphics/render_commands/ClearCommand.hpp>
#include <graphics/render_commands/RenderPipeline.hpp>

hexen::editor::EditorGameLoop::EditorGameLoop(const std::shared_ptr<hexen::engine::core::Window> &newWindow, const std::shared_ptr<hexen::engine::graphics::RenderContext> &renderContext) : GameLoop(newWindow)
{
	HEXEN_ADD_TO_PROFILE()
	systemManager = hexen::engine::core::memory::make_shared<hexen::editor::systems::EditorSystemsManager>();

	HEXEN_ASSERT(systemManager != nullptr, "System manager is nullptr!");

	systems::EditorSystemsManager::setCurrentSystemManager(systemManager.get());

	editorGui = engine::core::memory::make_shared<gui::EditorGUI>(window , renderContext);
}

hexen::editor::EditorGameLoop::~EditorGameLoop()
{
	HEXEN_ADD_TO_PROFILE()
	systems::EditorSystemsManager::setCurrentSystemManager(nullptr);
}


void hexen::editor::EditorGameLoop::start()
{
	HEXEN_ADD_TO_PROFILE()
	auto manager = std::dynamic_pointer_cast<systems::EditorSystemsManager>(systemManager);

	HEXEN_ASSERT(manager != nullptr, "Failed cast to EditorSystemsManager!");

	manager->setEditorGUI(editorGui);

	GameLoop::start();
}


void hexen::editor::EditorGameLoop::loop()
{
	HEXEN_ADD_TO_PROFILE()
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

		engine::graphics::ClearCommand command(glm::vec4(0.39f, 0.58f, 0.93f, 1.f));
		command.execute();

		editorGui->begin();
		editorGui->draw();
		editorGui->renderFrameBufferWindowsContents();
		systemManager->render(getAlpha());
		editorGui->end();

		window->swapBuffers();
		engine::threads::TaskSystem::waitForCounter();
		HEXEN_END_PROFILE_FRAME()
	}
}

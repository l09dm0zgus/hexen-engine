//
// Created by cx9ps3 on 01.08.2023.
//

#include "EditorSystemsManager.hpp"
#include "../components/EditorCameraComponent.hpp"
#include "../gui/EditorGUI.hpp"
#include "../gui/editors_windows/FramebufferWindow.hpp"
#include "EditorRenderSystem.hpp"
#include "core/window/Window.hpp"
#include "profiling/Profiling.hpp"
#include "systems/graphics/RenderSystem.hpp"
#include "systems/input/InputHelper.hpp"
#include <threading/TaskSystem.hpp>


void hexen::editor::systems::EditorSystemsManager::setEditorGUI(const std::shared_ptr<hexen::editor::gui::EditorGUI> &newEditorGUI)
{
	HEXEN_ADD_TO_PROFILE();
	editorGui = newEditorGUI;
	getInputSystem()->addGUI(newEditorGUI);
}

void hexen::editor::systems::EditorSystemsManager::processInput(const std::shared_ptr<hexen::engine::core::Window> &window)
{
	HEXEN_ADD_TO_PROFILE()
	SystemsManager::processInput(window);
}

void hexen::editor::systems::EditorSystemsManager::start()
{
	HEXEN_ADD_TO_PROFILE()
	SystemsManager::start();
}

void hexen::editor::systems::EditorSystemsManager::render(float alpha)
{
	HEXEN_ADD_TO_PROFILE()
	SystemsManager::render(alpha);

	auto windowSize = editorGui->getDockspace()->getWindow("Scene")->getSize();
	if (windowSize != currentSceneWindowSize)
	{
		hexen::engine::threads::TaskSystem::addTask(
				hexen::engine::core::threading::TaskPriority::Normal, +[](glm::vec2 windowSize)
																	  {
																		  using namespace hexen::engine::systems;
																		  RenderSystem::getMainCamera()->updateProjectionMatrix(windowSize.x, windowSize.y);
																	  },
				windowSize);

		currentSceneWindowSize = windowSize;
	}
	auto framebufferWindows = editorGui->getDockspace()->getListOfFramebufferWindows();
	std::for_each(framebufferWindows.begin(), framebufferWindows.end(),[this](const std::shared_ptr<gui::FramebufferWindow> &framebufferWindow){
				this->debugRenderSystem->updateCameraMatricesByWindowUUID(framebufferWindow->getSize(),framebufferWindow->getUUID());
	});

	debugRenderSystem->render(alpha);
}
void hexen::editor::systems::EditorSystemsManager::update(float deltaTime)
{
	HEXEN_ADD_TO_PROFILE()
	SystemsManager::update(deltaTime);
	debugRenderSystem->setDeltaTimeForCameras(deltaTime);
}

hexen::editor::systems::EditorSystemsManager::EditorSystemsManager() : SystemsManager()
{
	HEXEN_ADD_TO_PROFILE()
	debugRenderSystem = engine::core::memory::make_shared<EditorRenderSystem>();
}

//
// Created by cx9ps3 on 01.08.2023.
//

#include "EditorSystemsManager.hpp"
#include "core/window/Window.hpp"
#include <systems/TaskSystem.hpp>
#include <systems/RenderSystem.hpp>
#include "../gui/EditorGUI.hpp"
#include "DebugRenderSystem.hpp"
#include <profiling/Profiling.h>

void hexen::editor::systems::EditorSystemsManager::setEditorGUI(const std::shared_ptr<hexen::editor::gui::EditorGUI> &newEditorGUI)
{
    editorGui  = newEditorGUI;
    inputSystem->addGUI(newEditorGUI);
}

void hexen::editor::systems::EditorSystemsManager::processInput(const std::shared_ptr<hexen::engine::core::Window> &window)
{
    ADD_FUNCTION_TO_PROFILING
    SystemsManager::processInput(window);
}

void hexen::editor::systems::EditorSystemsManager::start()
{
    ADD_FUNCTION_TO_PROFILING

    currentSceneWindowSize = editorGui->getDockspace()->getWindow("Scene")->getSize();
    hexen::engine::systems::RenderSystem::addCameraComponent<hexen::engine::components::graphics::CameraComponent>(currentSceneWindowSize.x,currentSceneWindowSize.y,25.0f);

    SystemsManager::start();

    hexen::engine::systems::TaskSystem::addTask(hexen::engine::core::threading::TaskPriority::High,debugRenderSystem.get(),&DebugRenderSystem::start);
}

void hexen::editor::systems::EditorSystemsManager::render(float alpha)
{
    ADD_FUNCTION_TO_PROFILING
    SystemsManager::render(alpha);

    auto windowSize = editorGui->getDockspace()->getWindow("Scene")->getSize();
    if(windowSize != currentSceneWindowSize)
    {
        hexen::engine::systems::TaskSystem::addTask(hexen::engine::core::threading::TaskPriority::Normal,+[](glm::vec2 windowSize){
            hexen::engine::systems::RenderSystem::getMainCamera()->updateProjectionMatrix(windowSize.x,windowSize.y);
        },windowSize);

        currentSceneWindowSize = windowSize;
    }

    debugRenderSystem->render(alpha);
}
void hexen::editor::systems::EditorSystemsManager::update(float deltaTime)
{
    ADD_FUNCTION_TO_PROFILING
    SystemsManager::update(deltaTime);
}

void hexen::editor::systems::EditorSystemsManager::addDebugGrid()
{
    ADD_FUNCTION_TO_PROFILING
    debugRenderSystem->addDebugGrid();
}

hexen::editor::systems::EditorSystemsManager::EditorSystemsManager() : SystemsManager()
{
    ADD_FUNCTION_TO_PROFILING
    debugRenderSystem = std::make_shared<DebugRenderSystem>(100);
}

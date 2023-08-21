//
// Created by cx9ps3 on 01.08.2023.
//

#include "EditorSystemsManager.h"
#include <core/window/Window.h>
#include <systems/TaskSystem.h>
#include <systems/RenderSystem.h>
#include "../gui/EditorGUI.h"
#include "DebugRenderSystem.h"
#include <profiling/Profiling.h>

void edit::sys::EditorSystemsManager::setEditorGUI(const std::shared_ptr<gui::EditorGUI> &newEditorGUI)
{
    editorGui  = newEditorGUI;
}

void edit::sys::EditorSystemsManager::processInput(const std::shared_ptr<core::Window> &window)
{
    ADD_FUNCTION_TO_PROFILING
    SDL_Event event;
    while (window->pollEvents(&event))
    {
        editorGui->processEvent(&event);
        if (event.type == SDL_EVENT_QUIT || event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
        {
            window->close();
        }
        else if (event.type == SDL_EVENT_WINDOW_RESIZED)
        {
            window->resize();
        }
    }
    window->pollEvents(&event);
}

void edit::sys::EditorSystemsManager::start()
{
    ADD_FUNCTION_TO_PROFILING
    auto windowSize = editorGui->getDockspace()->getWindow("Scene")->getSize();
    ::sys::RenderSystem::addCameraComponent<::comp::CameraComponent>(windowSize.x,windowSize.y,45.0f);
    SystemsManager::start();
    ::sys::TaskSystem::addTask(::core::threading::TaskPriority::High,debugRenderSystem.get(),&DebugRenderSystem::start);
}

void edit::sys::EditorSystemsManager::render(float alpha)
{
    ADD_FUNCTION_TO_PROFILING
    SystemsManager::render(alpha);

    auto windowSize = editorGui->getDockspace()->getWindow("Scene")->getSize();
    ::sys::RenderSystem::getMainCamera()->updateProjectionMatrix(windowSize.x,windowSize.y);
    ::sys::TaskSystem::addTask(::core::threading::TaskPriority::High,debugRenderSystem.get(),&DebugRenderSystem::render,alpha);

}
void edit::sys::EditorSystemsManager::update(float deltaTime)
{
    ADD_FUNCTION_TO_PROFILING
    SystemsManager::update(deltaTime);
}

void edit::sys::EditorSystemsManager::addDebugGrid()
{
    ADD_FUNCTION_TO_PROFILING
    debugRenderSystem->addDebugGrid();
}

edit::sys::EditorSystemsManager::EditorSystemsManager()
{
    ADD_FUNCTION_TO_PROFILING
    debugRenderSystem = std::make_shared<DebugRenderSystem>(100);
}

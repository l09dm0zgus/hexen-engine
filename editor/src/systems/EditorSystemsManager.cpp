//
// Created by cx9ps3 on 01.08.2023.
//

#include "EditorSystemsManager.h"
#include <core/window/Window.h>
#include <systems/TaskSystem.h>
#include <systems/RenderSystem.h>
#include "../gui/EditorGUI.h"
#include "DebugRenderSystem.h"

void edit::sys::EditorSystemsManager::setEditorGUI(const std::shared_ptr<gui::EditorGUI> &newEditorGUI)
{
    editorGui  = newEditorGUI;
}

void edit::sys::EditorSystemsManager::processInput(const std::shared_ptr<core::Window> &window)
{
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
    auto windowSize = editorGui->getDockspace()->getWindow("Scene")->getSize();
    ::sys::RenderSystem::addCameraComponent<::comp::CameraComponent>(windowSize.x,windowSize.y,45.0f);
    SystemsManager::start();
    ::sys::TaskSystem::addTask(::core::threading::TaskPriority::High,debugRenderSystem.get(),&DebugRenderSystem::start);
}

void edit::sys::EditorSystemsManager::render(float alpha)
{
    SystemsManager::render(alpha);
    ::sys::TaskSystem::addTask(::core::threading::TaskPriority::High,debugRenderSystem.get(),&DebugRenderSystem::render,alpha);

}

void edit::sys::EditorSystemsManager::update(float deltaTime)
{
    SystemsManager::update(deltaTime);
}

void edit::sys::EditorSystemsManager::addDebugGrid()
{
    debugRenderSystem->addDebugGrid();
}

edit::sys::EditorSystemsManager::EditorSystemsManager()
{
    debugRenderSystem = std::make_shared<DebugRenderSystem>(100);
}

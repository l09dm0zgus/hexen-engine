//
// Created by cx9ps3 on 01.08.2023.
//

#include <systems/TaskSystem.h>
#include <core/window/Window.h>
#include "../gui/EditorGUI.h"
#include "EditorGameLoop.h"
#include "../systems/EditorSystemsManager.h"

edit::EditorGameLoop::EditorGameLoop()
{
    systemManager = core::mem::make_shared<sys::EditorSystemsManager>();

    HEXEN_ASSERT(systemManager != nullptr , "System manager is nullptr!");

    sys::EditorSystemsManager::setCurrentSystemManager(systemManager.get());


}

edit::EditorGameLoop::~EditorGameLoop()
{
    sys::EditorSystemsManager::setCurrentSystemManager(nullptr);
}

void edit::EditorGameLoop::start()
{
    GameLoop::start();
}

void edit::EditorGameLoop::loop(const std::shared_ptr<core::Window> &window)
{
    initializeClock();

    editorGui = core::mem::make_shared<gui::EditorGUI>(window->getSDLWindow(),window->getGLContext());

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

        //render
        window->clear();
        editorGui->begin();
        editorGui->draw();
        systemManager->render(getAlpha());
        editorGui->end();
        window->swapBuffers();
        ::sys::TaskSystem::waitForCounter();
    }
}

//
// Created by cx9ps3 on 01.08.2023.
//

#include <systems/TaskSystem.h>
#include <core/scene/SceneManager.h>
#include <core/window/Window.h>
#include "../gui/EditorGUI.h"
#include "EditorGameLoop.h"
#include "../systems/EditorSystemsManager.h"
#include <profiling/Profiling.h>


edit::EditorGameLoop::EditorGameLoop(const std::shared_ptr<core::Window> &newWindow) : core::GameLoop(newWindow)
{
    systemManager = core::mem::make_shared<sys::EditorSystemsManager>();

    HEXEN_ASSERT(systemManager != nullptr , "System manager is nullptr!");

    sys::EditorSystemsManager::setCurrentSystemManager(systemManager.get());

    editorGui = core::mem::make_shared<gui::EditorGUI>(newWindow->getSDLWindow(),newWindow->getGLContext());
}

edit::EditorGameLoop::~EditorGameLoop()
{
    sys::EditorSystemsManager::setCurrentSystemManager(nullptr);
}


void edit::EditorGameLoop::start()
{
    ADD_FUNCTION_TO_PROFILING
    auto manager = std::dynamic_pointer_cast<sys::EditorSystemsManager>(systemManager);

    HEXEN_ASSERT(manager != nullptr , "Failed cast to EditorSystemsManager!");

    manager->setEditorGUI(editorGui);

    GameLoop::start();
}


void edit::EditorGameLoop::loop()
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

        if(core::SceneManager::getCurrentScene() != nullptr)
        {
            auto manager = std::dynamic_pointer_cast<sys::EditorSystemsManager>(systemManager);

            HEXEN_ASSERT(manager != nullptr,"Failed cast pointer to EditorSystemsManager");

            manager->addDebugGrid();
        }
        window->clear();

        editorGui->bindFramebuffer();
        systemManager->render(getAlpha());
        editorGui->unbindFramebuffer();


        editorGui->begin();
        editorGui->draw();
        editorGui->end();

        window->swapBuffers();
        ::sys::TaskSystem::waitForCounter();
        END_FRAME
    }
}

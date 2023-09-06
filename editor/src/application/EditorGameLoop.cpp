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


hexen::editor::EditorGameLoop::EditorGameLoop(const std::shared_ptr<hexen::engine::core::Window> &newWindow) : hexen::engine::core::GameLoop(newWindow)
{
    systemManager = hexen::engine::core::memory::make_shared<hexen::editor::systems::EditorSystemsManager>();

    HEXEN_ASSERT(systemManager != nullptr , "System manager is nullptr!");

    systems::EditorSystemsManager::setCurrentSystemManager(systemManager.get());

    editorGui = engine::core::memory::make_shared<gui::EditorGUI>(newWindow->getSDLWindow(),newWindow->getGLContext());
}

hexen::editor::EditorGameLoop::~EditorGameLoop()
{
    systems::EditorSystemsManager::setCurrentSystemManager(nullptr);
}


void hexen::editor::EditorGameLoop::start()
{
    ADD_FUNCTION_TO_PROFILING
    auto manager = std::dynamic_pointer_cast<systems::EditorSystemsManager>(systemManager);

    HEXEN_ASSERT(manager != nullptr , "Failed cast to EditorSystemsManager!");

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

        if(engine::core::SceneManager::getCurrentScene() != nullptr)
        {
            auto manager = std::dynamic_pointer_cast<systems::EditorSystemsManager>(systemManager);

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
        engine::systems::TaskSystem::waitForCounter();
        END_FRAME
    }
}

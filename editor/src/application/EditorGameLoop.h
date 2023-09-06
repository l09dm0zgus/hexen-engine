//
// Created by cx9ps3 on 01.08.2023.
//

#pragma once
#include <core/application/GameLoop.h>

namespace hexen::engine::core
{
    class Window;
}

namespace hexen::editor::gui
{
    class EditorGUI;
}

namespace hexen::editor
{
    /**
    * @class EditorGameLoop
    * @brief A class that handles the main game loop in editor.
    *
    * The EditorGameLoop class encapsulates the logic for running the main game loop. It controls the game's update
    * and rendering processes while taking care of timing and frame rate control.
    */


    class EditorGameLoop : public hexen::engine::core::GameLoop
    {
    public:

        /**
       * @brief Initialize TaskSystem , allocating memory for DebugSystemsManager,EditorGUI objects,
       * and setting pointer to current system manager
       */

        explicit EditorGameLoop(const std::shared_ptr<hexen::engine::core::Window> &newWindow);


        /**
         * @brief Virtual destructor,because class has virtual methods.
         * Just setting pointer to current system manager to nullptr.
         */

        ~EditorGameLoop() override;

        EditorGameLoop(const EditorGameLoop&) = delete;


        EditorGameLoop(EditorGameLoop&&) = delete;

        EditorGameLoop& operator=(const EditorGameLoop&) = delete;

        EditorGameLoop& operator=(EditorGameLoop&&) = delete;

        /**
        * @brief Adds to SystemsManager systems,and then them starts.
        */

        void start() override;

        /**
        * @brief Executes a loop that continuously updates and renders.
        *
        * The loop function takes a shared pointer to a Window object and continuously performs
        * the following steps until the window is closed:
        * 1. Updates processing input events, updating game logic, etc.
        * 2. Renders objects, applying effects, etc.
        *
        */

        void loop() override;
    private:
        std::shared_ptr<gui::EditorGUI> editorGui;
    };

}

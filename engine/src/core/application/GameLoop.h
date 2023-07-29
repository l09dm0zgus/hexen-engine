//
// Created by cx9ps3 on 29.07.2023.
//

#pragma once
#include "../memory_pool/AllocatedObject.h"
#include "../../systems/SystemManager.h"
#include <chrono>

namespace core
{
    class Window;

    /**
    * @class GameLoop
    * @brief A class that handles the main game loop.
    *
    * The GameLoop class encapsulates the logic for running the main game loop. It controls the game's update
    * and rendering processes while taking care of timing and frame rate control.
    */

    class GameLoop : public mem::AllocatedObject
    {
    public:

        /**
         * @brief Initialize TaskSystem , allocating memory for SystemManager object,
         * and setting pointer to current system manager
         */

        GameLoop();


        /**
         * @brief Virtual destructor,because class has virtual methods.
         * Just setting pointer to current system manager to nullptr.
         */

        virtual ~GameLoop();

        GameLoop(const GameLoop&) = delete;


        GameLoop(GameLoop&&) = delete;

        GameLoop& operator=(const GameLoop&) = delete;

        GameLoop& operator=(GameLoop&&) = delete;

        /**
        * @brief Adds to SystemManager systems,and then them starts.
        */

        virtual void start();

        /**
        * @brief Executes a loop that continuously updates and renders the given window.
        *
        * The loop function takes a shared pointer to a Window object and continuously performs
        * the following steps until the window is closed:
        * 1. Updates processing input events, updating game logic, etc.
        * 2. Renders objects, applying effects, etc.
        *
        * @param window A shared pointer to the Window object to update and render.
        */

        virtual void loop(const std::shared_ptr<Window> &window);
    protected:

        /**
        * @brief Initializes the clock used for the game loop.
        *
        * This function is responsible for creating and initializing the clock
        * used in the game loop of the core::GameLoop class.
        *
        *
        * @see core::GameLoop
        *
        */

        void initializeClock();

        /**
        * @brief Sets the start time of the current frame in the game loop.
        *
        * This function is responsible for setting the start time of the current frame in the game loop.
        * The frame start time is used to calculate the frame duration and to synchronize various game elements.
        *
        * @note The frame start time should be set before any processing of the current frame.
        *
        * @see core::GameLoop
        *
        */

        void setFrameStart();

        /**
        * @brief Sets the accumulator value for the game loop.
        *
        * This function is used in the game loop to set the value of the accumulator.
        * The accumulator is a variable that keeps track of the elapsed time since the last frame update.
        * It is important for timing calculations and achieving consistent gameplay regardless of frame rate.
        *
        */

        void setAccumulator();


        /**
        * @brief Calculating interpolated value for rendering.
        */

        float getAlpha();

        std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<double>> framesStart;

        /**
        * @brief The maximum number of frames per second to be rendered.
        *
        * This variable represents the limit for the number of frames per second (FPS) that should be rendered by the application.
        * It is expressed as a floating-point value, specifically a single-precision floating-point number (float).
        * The default value is 240.0.
        *
        * @note The FPS can be adjusted according to the performance capabilities of the hardware
        *       and the specific requirements of the application being developed.
        */

        const float framesLimit{240.0f};

        /**
        * @brief Represents the time interval between frames.
        *
        * The deltaTime variable is calculated as the reciprocal of the framesLimit.
        * It is used in time-based calculations to ensure consistent behavior across different frame rates.
        * By multiplying deltaTime with other time-dependent variables, it allows for frame rate-independent gameplay logic.
        *
        *
        * @note It is important to ensure that the framesLimit value is non-zero to avoid division by zero.
        *
        * @see framesLimit
        */

        const float deltaTime = 1 / framesLimit;

        float accumulator{0};

        const float msPerUpdate{0.2f};

        std::shared_ptr<sys::SystemManager> systemManager;
    };
}



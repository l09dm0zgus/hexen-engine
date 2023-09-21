//
// Created by cx9ps3 on 29.07.2023.
//

#pragma once
#include "../../systems/SystemsManager.hpp"
#include "../memory_pool/AllocatedObject.hpp"
#include <chrono>

namespace hexen::engine::core
{
	class Window;

	/**
    * @class GameLoop
    * @brief A class that handles the main game loop.
    *
    * The GameLoop class encapsulates the logic for running the main game loop. It controls the game's update
    * and rendering processes while taking care of timing and frame rate control.
    */

	class GameLoop : public memory::AllocatedObject
	{
	public:
		/**
         * @brief Initialize TaskSystem , allocating memory for SystemsManager object,
         * and setting pointer to current system manager
         */

		explicit GameLoop(const std::shared_ptr<Window> &newWindow);


		/**
         * @brief Virtual destructor,because class has virtual methods.
         * Just setting pointer to current system manager to nullptr.
         */

		~GameLoop() override;

		/**
 		* @brief Deleted copy constructor.
 		*
 		* This is to prevent copying of an object of this class.
 		*
 		* @param GameLoop is a const GameLoop reference.
 		*/

		GameLoop(const GameLoop &) = delete;


		/**
 		* @brief Deleted move constructor.
 		*
 		* This is to prevent moving of an object of this class.
 		*
 		* @param GameLoop is a rvalue reference to a GameLoop object.
 		*/

		GameLoop(GameLoop &&) = delete;


		/**
 		* @brief Deleted copy assignment operator.
 		*
 		* This is to prevent assignment of an object of this class.
 		*
 		* @param GameLoop is a const GameLoop reference.
 		* @return GameLoop reference.
 		*/

		GameLoop &operator=(const GameLoop &) = delete;


		/**
 		* @brief Deleted move assignment operator.
 		*
 		* This is to prevent move assignment of an object of this class.
 		*
 		* @param GameLoop is a rvalue reference to a GameLoop object.
 		* @return GameLoop reference.
 		*/

		GameLoop &operator=(GameLoop &&) = delete;

		/**
        * @brief Adds to SystemsManager systems,and then them starts.
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
        */

		virtual void loop();

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

		double getAlpha();

		std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<double>> framesStart;

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

		const double framesLimit {240.0f};

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

		/**
  		* @var const double deltaTime
  		* The time difference between each frame/update. It is the inverse of the frame rate limit.
  		*/

		const double deltaTime = 1 / framesLimit;

		/**
  		* @var double accumulator
  		* This variable accumulates the frame time that has not yet been processed/used for game update calls.
  		*
  		* This can be used in the context of 'fixed timestep' where we want to have a consistent game
  		* update frame rate regardless of rendering speed variations, consumption of accumulated time
  		* in multiple smaller fixed-size increments allows smoother frame rate instead of hiccoughs
  		* in game speed when the rendering speed drops below set limit.
  		*
  		* For example, if our frame rate drops to half of what it should be and accumulator reaches a
  		* value of 2*msPerUpdate or more, instead of updating game state in a single double speed
  		* update (which would make in-game characters move in large jerks), we instead do two normal
  		* speed update calls, which results in same game speed but smoother visual result.
  		*/

		double accumulator {0.0};

		/**
  		* @var const double msPerUpdate
  		* Defines how much time passes in in-game world per each fixed modifier update.
  		* Using non-whole number value allows game speed independent from frame rate
  		* (games will run at same speed on faster and slower computers).
  		*/

		const double msPerUpdate {0.2};

		/**
  		* @var std::shared_ptr<systems::SystemsManager> systemManager
  		* A smart pointer to the system manager object.
  		*
  		* As this is a shared_ptr, it allows shared ownership of the object meaning
  		* SystemsManager can be owned by multiple entities and will only be deleted
  		* when the last one stops referencing it.
  		*/

		std::shared_ptr<systems::SystemsManager> systemManager;

		/**
  		* @var std::shared_ptr<Window> window
  		* A smart pointer to the window object.
  		*
  		* Like the systemManager above, as this is a shared_ptr it allows shared ownership
  		* of the object meaning window can be owned by multiple entities and will only be deleted
  		* when the last one stops referencing it.
  		*/

		std::shared_ptr<Window> window;
	};
}// namespace hexen::engine::core

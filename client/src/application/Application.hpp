//
// Created by cx9ps3 on 30.12.22.
//
#pragma once

#include "systems/GameLoop.hpp"
#include <core/window/Window.hpp>

namespace hexen::client
{
	/**
	 * @class Application
	 *
	 * @brief Manages application runtime lifecycle.
	 *
	 * A class that encapsulates window and settings, controlling the
	 * application's runtime lifecycle. It defines behavior for creating,
	 * copying and running the application.
	 * It is designed with the rule of five to be non-copyable and non-movable.
	 */

	class Application
	{
	public:

		/**
		 * @brief Default constructor.
		 *
		 * Construct a new Application object.
		 */

		Application();

		/**
		 * @brief Default destructor.
		 *
		 * Destroy the Application object.
		 */

		~Application() = default;

		/**
		 * @brief Delete copy constructor.
		 *
		 * Prevent the creation of new Application through copying.
		 *
		 * @param application The object to copy from.
		 */

		Application(const Application &application) = delete;

		/**
		 * @brief Delete move constructor.
		 *
		 * Prevent the creation of new Application through moving.
		 *
		 * @param application The object to move from.
		 */

		Application(Application &&application) = delete;

		/**
		 * @brief Delete assignment operator.
		 *
		 * Prevent assignment through copying.
		 *
		 * @param application The object to copy from.
		 * @return Reference to this object.
		 */

		Application &operator=(const Application &application) = delete;

		/**
		 * @brief Delete move assignment operator.
		 *
		 * Prevent assignment through moving.
		 *
		 * @param application The object to move from.
		 * @return Reference to this object.
		 */

		Application &operator=(Application &&application) = delete;

		/**
		 * @brief Run the application.
		 *
		 * Contains the main loop of the application (events handling,
		 * update, draw).
		 */

		void run();

	private:

		/**
		 * @brief A shared pointer to Window object.
		 *
		 * Represents the window of the application.
		 */

		std::shared_ptr<engine::core::Window> window;

		/**
		 * @brief An object of Settings.
		 *
		 * Represents the settings of the application.
		 */

		engine::core::Settings settings;

		std::unique_ptr<engine::core::GameLoop> gameLoop;
	};

}// namespace hexen::engine::core

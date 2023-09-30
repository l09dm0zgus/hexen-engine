//
// Created by cx9ps3 on 25.05.2023.
//

#pragma once
#include "EditorGameLoop.hpp"
#include <core/window/Window.hpp>

namespace hexen::editor
{
	/**
 	* @class Application
 	* @brief A class representing the application.
 	*
 	* The Application class encapsulates the core logic
 	* and resources of the HexenEngine.
 	*/

	class Application
	{
	public:
		/**
	 	* @brief Construct a new Application object.
	 	*
	 	* Default constructor for Application. Initializes
	 	* the object's state such as window, main game loop, and settings.
	 	*/

		Application();

		/**
	 	* @brief Runs the application.
	 	*
	 	* This method contains the main loop of the application.
	 	*/

		void run();

	private:
		/**
	 	* @brief A shared pointer holding a reference to the window.
	 	*/

		std::shared_ptr<hexen::engine::core::Window> window;

		/**
	 	* @brief A unique pointer holding a reference to the main game loop.
	 	*/

		std::unique_ptr<EditorGameLoop> mainGameLoop;

		/**
	 	* @brief A settings object holding the game settings.
	 	*/

		hexen::engine::core::Settings settings;
	};
	;

}// namespace hexen::editor

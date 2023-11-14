//
// Created by cx9ps3 on 25.05.2023.
//

#pragma once
#include "EditorGameLoop.hpp"
#include <core/window/Window.hpp>

namespace hexen::engine::core::assets
{
	class AssetsStorage;
}

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

		/**
 		* @brief Fetches the name of the application from the application settings.
 		*
 		* This function creates a constant instance of `engine::core::Settings`
 		* using the default constructor and fetches the application's name from it.
 		*
 		* @return Returns the name of the application as std::string.
 		*
 		*/

		static std::string getName();

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
		std::shared_ptr<engine::graphics::RenderContext> renderContext;

	};

}// namespace hexen::editor

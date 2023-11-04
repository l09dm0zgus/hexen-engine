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

		static std::shared_ptr<hexen::engine::core::assets::AssetsStorage> getEditorAssetsStorage();

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

		/**
 		* @brief Gets a pointer to the Editor Asset Storage.
 		*
 		* This function returns a shared pointer to an AssetStorage object
 		* that is associated with the name specified.
 		*
 		* @return A shared_ptr to an AssetStorage object.
 		*/

		static std::string name;
	};

}// namespace hexen::editor

//
// Created by cx9ps3 on 28.12.22.
//

#pragma once

#include "../../graphics/render_context/RenderContext.hpp"
#include "../application/Settings.hpp"
#include "../memory_pool/AllocatedObject.hpp"
#include <SDL3/SDL.h>
#include <string>


namespace hexen::engine::core
{
	/**
 	* @brief Constant Iterator to the end of the collection.
 	* This is identical to end() but is used where the object is
 	* constant and allows for interface uniformity with non-constant objects.
 	* @return A ConstIterator pointing to past-the-end element.
 	*/

	class Window : public memory::AllocatedObject
	{
	public:
		/**
        * @class hexen::engine::core::Window
        * @brief The Window class represents a window in the game engine.
        *
        * The Window class is responsible for creating and managing a game window. It takes a reference to a Settings object
        * which contains the necessary configuration settings for the window.
        */

		explicit Window(const Settings &settings);

		/**
        * @class hexen::engine::core::Window
        * @brief The Window class represents a window in the game engine.
        *
        * The Window class provides functionality to create, destroy, and interact
        * with a window in the game engine. This class is responsible for managing
        * the operating system specific window, handling user input, and rendering
        * graphics.
        */

		~Window() override;

		/**
        * @brief Swaps the front and back buffers of the window.
        *
        * This function is responsible for swapping the buffers of the window, which allows
        * the rendered content to be displayed on the screen. It should be called after
        * rendering the frame to update the display.
        *
        * @attention This function should only be called once per frame.
        */

		void swapBuffers();

		/**
 		*  @brief This method is used to close the window
 		*  in the HexenEngine.
 		*
 		*  @details When this method is called, it will simply set
 		*  the bool variable bIsOpen to false which results in the
 		*  window being closed.
 		*
 		*
 		*/

		void close();

		/**
        * @brief Clears the contents of the Window.
        *
        * This function clears the contents of the Window by setting the background color
        * to the specified clear color.
        *
        */

		void clear();

		/**
        * @brief Resizes the window to the specified dimensions.
        *
        * This function resizes the window to the given width and height, in pixels.
        * Any contents rendered within the window will be adjusted accordingly.
        * As a consequence of resizing, the viewport and aspect ratio may also change.
        *
        */


		void resize();

		/**
        * @class hexen::engine::core::Window
        * @brief Represents the window used in the game engine.
        *
        * The Window class provides methods to retrieve the size of the window.
        */

		glm::vec2 getSize();

		/**
        * @brief Check if the window is open.
        *
        * A member function of the Window class in the hexen::engine::core namespace.
        * This function returns a boolean value indicating whether the window is open or not.
        *
        * @return True if the window is open, false otherwise.
        */

		[[nodiscard]] bool isOpen() const noexcept;

		/**
 		* @brief      Poll SDL events from event queue.
 		*
 		* This function polls for currently pending SDL events. It returns the next event available, or 0 if there are no more events.
 		*
		* @param      sdlEvent  The SDL Event pointer to store the polled event.
 		*
 		* @return     Returns 1 if there is a pending event or 0 if there are none available.
 		*
 		* @note       If the function succeeds, the data in the event structure is modified.
 		*/

		i32 pollEvents(SDL_Event *sdlEvent);

		/**
        * @brief Get the current display mode of the window.
        *
        * This function returns the current display mode of the window, including information such as the width, height, bit depth, and refresh rate.
        * The returned display mode is in the hexen::engine::core::DisplayMode structure format.
        *
        * @return The current display mode of the window in hexen::engine::core::DisplayMode structure format.
        *
        * @note This function is guaranteed to be noexcept.
        */


		[[nodiscard]] SDL_DisplayMode getDisplayMode() const noexcept;

		/**
        * @brief Get the SDL window instance.
        *
        * This function is used to retrieve the SDL window created by the Window class.
        *
        * @return The SDL_Window pointer representing the window instance.
        */

		[[nodiscard]] SDL_Window *getSDLWindow() const noexcept;

		/**
        * @brief Get the RenderContext instance.
        *
        * @return The raw pointer to RenderContext.
        */

		graphics::RenderContext *getRenderContext() const noexcept;

	private:
		Settings settings;

		/**
        * @brief Initializes the SDL library for the Window class.
        *
        * This function initializes the Simple DirectMedia Layer (SDL) library
        * for the Window class, which provides a platform-independent interface
        * for rendering graphics and handling input events.
        *
        */

		void initSDL();

		/**
		* @brief Holds information about the display mode.
		*/

		SDL_DisplayMode displayMode {};

		/**
		* @brief Pointer to the SDL_Window structure, representing window to be created.
		*/

		SDL_Window *window {nullptr};

		/**
		* @brief  Holds the height of the window, default is 720.
		*/

		i32 height {720};

		/**
		* @brief  Holds the width of the window, default is 1280.
		*/

		i32 width {1280};

		/**
		* @brief  Variable for Window's title.
		*/

		std::string title;

		/**
		* @brief  Boolean variable indicating if the window is open or not. Default is true (open).
		*/

		bool bIsOpen {true};

		/**
 		* @brief Sets the icon of the object by path.
 		*
 		* This function is used to set the icon for an object, the icon will be loaded from a path provided.
 		*
 		* @param pathToIcon The filesystem path to the icon file.
 		*/

		void setIcon(const std::string &pathToIcon);

		/**
    	* @brief A surface containing the window's icon.
    	*/

		SDL_Surface *icon {};

		/**
    	* @brief The rendering context, abstracting rendering specifics.
    	*/

		std::unique_ptr<graphics::RenderContext> renderContext;

		/**
    	* @brief Creates the SDL window.
    	*/

		void createSDLWindow();
	};
}// namespace hexen::engine::core

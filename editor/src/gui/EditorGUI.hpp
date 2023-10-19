//
// Created by cx9ps3 on 25.05.2023.
//

#pragma once

#include "Dockspace.hpp"
#include "Style.hpp"
#include <SDL3/SDL.h>
#if defined(_ENABLE_OPENGL_SUPPORT)
	#include <backends/imgui_impl_opengl3.h>
	#include <backends/imgui_impl_opengl3_loader.h>
	#include <graphics/render_context/GL/GLRenderContext.hpp>
#endif
#include <backends/imgui_impl_sdl3.h>
#include <graphics/render_context/RenderContext.hpp>
#include <gui/IGUI.hpp>
#include <imgui.h>

namespace hexen::engine::core
{
	class Window;
}

namespace hexen::editor::gui
{
	using RenderContext = hexen::engine::graphics::RenderContext;
	using RenderAPI = hexen::engine::core::Settings::RenderAPI;

	/**
     * @class EditorGUI
     * @brief A class for handling the graphical user interface of the editor.
     *
     * This class provides functionality for managing the editor's graphical user interface.
     * It is responsible for creating and managing the main editor window, as well as handling
     * the OpenGL context for rendering the interface.
     */

	class EditorGUI : public hexen::engine::gui::IGUI
	{
	public:
		/**
        * @constructor  EditorGUI()
        * @brief Default constructor.
        *
        * Initializes an instance of EditorGUI.
        */

		explicit EditorGUI();

		/**
 		* @brief Constructs the EditorGUI for the specified window and rendering context.
 		*
 		* The constructor initializes ImGui library for OpenGL if the current rendering API is OpenGL.
 		* Note: The initializations for Vulkan and DirectX12 are not done and have to be implemented.
 		*
 		* @param window A shared pointer to `engine::core::Window` where the Editor GUI will be laid out.
 		* @param renderContext A shared pointer to `engine::graphics::RenderContext` which provides the rendering context for the GUI.
 		*
 		* @sa hexen::editor::gui::EditorGUI
 		*/

		explicit EditorGUI(const std::shared_ptr<engine::core::Window> &window, const std::shared_ptr<engine::graphics::RenderContext> &renderContext);

		/**
         * @desreuctor ~EditorGUI()
         * @brief Destructor.
         *
         * Frees up any resources within EditorGUI instance.
         */

		~EditorGUI() override;

		/**
        * @brief Starts the GUI of editor.
        *
        * This function is used to start the GUI of editor. It is responsible for initializing
        * the necessary components and displaying the initial state of the editor interface.
        *
        */
		void begin();

		/**
        * @brief Draws the GUI for the EditorGUI class.
        *
        * This function is responsible for drawing the graphical user interface (GUI) for the EditorGUI class. It renders all
        * the elements on the screen required for the editor.
        *
        * @note This function does not return anything.
        *
        * @see EditorGUI
        *
        * The function should be called after all the necessary elements have been initialized on the screen.
        */


		void draw();

		/**
        * @brief Flags the end of the editor.
        *
        * This function is used to flag the end of the editor. It performs any necessary cleanup or finalization procedures before closing the editor.
        *
        * @par Usage
        * Call this function when you want to signal the end of the editor.
        *
        * @par Example
        *  ```
        * EditorGUI editor;
        * // code for initializing the editor
        * editor.end();
        * ```
        */

		void end();

		/**
        * @brief Processes SDL events in the editor GUI.
        *
        * This function handles the SDL events and performs relevant actions in the editor GUI. It uses the provided SDL_Event
        * parameter to determine the type of event and takes appropriate actions accordingly.
        *
        * @param event SDL event to be processed.
        */

		void processEvent(const SDL_Event &event) override;

		/**
        * @brief Retrieves the dockspace for the EditorGUI.
        *
        * This function returns the dockspace object that is utilized in the EditorGUI class
        *
        * @return The dockspace object used by the EditorGUI.
        */

		std::shared_ptr<Dockspace> getDockspace();

		/**
 		* @brief Renders the content of each framebuffer window.
 		*
 		* This function gets a list of all framebuffer windows from the dockspace
 		* and calls the render function defined in the FrameBufferWindows class.
 		*
 		*/

		void renderFrameBufferWindowsContents();

	private:
		Style style;
		ImGuiIO *io {nullptr};
		std::shared_ptr<Dockspace> dockspace;
		RenderAPI currentRenderAPI;
	};
}// namespace hexen::editor::gui

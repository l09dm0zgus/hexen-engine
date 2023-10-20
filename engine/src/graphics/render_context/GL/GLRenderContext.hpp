//
// Created by cx9ps3 on 05.10.2023.
//

#pragma once
#include "../RenderContext.hpp"
#include <application/Settings.hpp>
#include "../profiling/Profiling.hpp"

namespace hexen::engine::graphics::gl
{
	/**
 	* @class GLRenderContext
 	* @brief A class that represents an OpenGL rendering context.
 	* @details This class is responsible for handling OpenGL-specific implementation
 	*          details of a rendering context.
 	*/

	class GLRenderContext : public RenderContext
	{
	private:
		/**
     	* @brief Represents OpenGL context.
     	*/

		SDL_GLContext glContext {nullptr};

		/**
     	* @brief Sets hint related to OpenGL settings.
     	* @param settings Contains different properties like resolution and full screen mode.
     	*/

		void setGLHints(const core::Settings &settings);

		/**
     	* @brief Initializes the GLEW library.
     	* @note GLEW (OpenGL Extension Wrangler Library) is used to access modern OpenGL API features.
     	*/

		void initializeGLEW() const;

		/**
     	* @brief Represents the structure which is corresponding to the OpenGL settings.
    	*/

		core::Settings::OpenGLSettings openGlSettings;

	protected:

		/**
     	* @brief Creates actual SDL rendering context for the given window.
     	* @param window A pointer to the SDL_Window structure, which is the window where rendering is done.
     	*/

		void createRenderContextForSDLWindow(SDL_Window *window);

	public:
		/**
     	* @brief Constructs a GLRenderContext with specified settings.
     	* @param settings Contains different properties like resolution and full screen mode.
     	*/

		explicit GLRenderContext(const core::Settings &settings);

		/**
 		* @fn SDL_GLContext hexen::engine::graphics::gl::GLRenderContext::getSDLGLContext() const noexcept
 		* @brief Get the SDL GL Context object.
 		*
 		* This method is utilized to obtain the SDL OpenGL context associated with the instance.
 		*
 		* @return SDL_GLContext The current instance's SDL_GLContext object.
 		*/

		[[nodiscard]] SDL_GLContext getSDLGLContext() const noexcept;

		void attachWindow(const std::shared_ptr<core::Window> &window) override;
	};
}// namespace hexen::engine::graphics::gl

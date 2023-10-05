//
// Created by cx9ps3 on 05.10.2023.
//

#pragma once
#include "../RenderContext.hpp"
#include <application/Settings.hpp>
namespace hexen::engine::graphics::gl
{
	class GLRenderContext : public RenderContext
	{
	private:

		/**
		* @brief  Represents OpenGL context.
		*/

		SDL_GLContext glContext {nullptr};

		void setGLHints(const core::Settings& settings);
		void initializeGLEW() const;

		core::Settings::OpenGLSettings openGlSettings;

	protected:
		[[nodiscard]] core::i32 getWindowFlags() const noexcept override;
		void createRenderContextForSDLWindow(SDL_Window *window) override;
	public:
		explicit GLRenderContext(const core::Settings& settings);

	};
}

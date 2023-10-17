//
// Created by cx9ps3 on 25.05.2023.
//

#include "Application.hpp"
#include <graphics/render_context/RenderContext.hpp>

hexen::editor::Application::Application()
{
	renderContext = hexen::engine::graphics::RenderContext::create();
	window = hexen::engine::core::memory::make_shared<hexen::engine::core::Window>(settings);
	renderContext->attachWindow(window);
	mainGameLoop = hexen::engine::core::memory::make_unique<EditorGameLoop>(window,renderContext);
}

void hexen::editor::Application::run()
{
	mainGameLoop->start();
	mainGameLoop->loop();
}

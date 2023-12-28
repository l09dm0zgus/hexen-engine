//
// Created by cx9ps3 on 30.12.22.
//

#include "Application.hpp"
void hexen::client::Application::run()
{
	gameLoop->start();
	gameLoop->loop();
}

hexen::client::Application::Application()
{
	renderContext = hexen::engine::graphics::RenderContext::create();
	window = hexen::engine::core::memory::make_shared<hexen::engine::core::Window>(settings);
	renderContext->attachWindow(window);
	gameLoop = hexen::engine::core::memory::make_unique<engine::systems::GameLoop>(window);
}

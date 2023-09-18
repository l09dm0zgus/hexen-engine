//
// Created by cx9ps3 on 25.05.2023.
//

#include "Application.hpp"


hexen::editor::Application::Application()
{
	window = hexen::engine::core::memory::make_shared<hexen::engine::core::Window>(settings);
	mainGameLoop = hexen::engine::core::memory::make_unique<EditorGameLoop>(window);
}

void hexen::editor::Application::run()
{
	mainGameLoop->start();
	mainGameLoop->loop();
}

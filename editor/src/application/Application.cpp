//
// Created by cx9ps3 on 25.05.2023.
//

#include "Application.hpp"
#include <graphics/render_context/RenderContext.hpp>
#include <core/assets/AssetsStorage.hpp>

hexen::editor::Application::Application()
{
	HEXEN_ADD_TO_PROFILE()
	renderContext = hexen::engine::graphics::RenderContext::create();
	window = hexen::engine::core::memory::make_shared<hexen::engine::core::Window>(settings);
	renderContext->attachWindow(window);
	mainGameLoop = hexen::engine::core::memory::make_unique<EditorGameLoop>(window,renderContext);
	engine::core::assets::AssetsStorage::addAssetsStorage(settings.getApplicationName(), std::filesystem::current_path());
}

void hexen::editor::Application::run()
{
	HEXEN_ADD_TO_PROFILE()
	mainGameLoop->start();
	mainGameLoop->loop();
}

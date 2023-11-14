//
// Created by cx9ps3 on 25.05.2023.
//

#include "Application.hpp"
#include <graphics/render_context/RenderContext.hpp>
#include <core/assets/AssetsStorage.hpp>

hexen::editor::Application::Application()
{
	HEXEN_ADD_TO_PROFILE()
	engine::core::assets::AssetsStorage::addDefaultStorage(std::filesystem::current_path() / "EngineData");
	engine::core::assets::AssetsStorage::addAssetsStorage(settings.getApplicationName(), std::filesystem::current_path() / "EditorData");

	renderContext = hexen::engine::graphics::RenderContext::create();
	window = hexen::engine::core::memory::make_shared<hexen::engine::core::Window>(settings);
	renderContext->attachWindow(window);
	mainGameLoop = hexen::engine::core::memory::make_unique<EditorGameLoop>(window,renderContext);
}

void hexen::editor::Application::run()
{
	HEXEN_ADD_TO_PROFILE()
	mainGameLoop->start();
	mainGameLoop->loop();
}

std::string hexen::editor::Application::getName()
{
	engine::core::Settings const settings;
	return settings.getApplicationName();
}

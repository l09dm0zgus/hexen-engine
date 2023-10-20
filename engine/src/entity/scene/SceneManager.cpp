//
// Created by cx9ps3 on 11.07.2023.
//

#include "SceneManager.hpp"
#include "../profiling/Profiling.hpp"
std::shared_ptr<hexen::engine::core::Scene> hexen::engine::core::SceneManager::currentScene;

void hexen::engine::core::SceneManager::loadScene(const std::string &path)
{
	HEXEN_ADD_TO_PROFILE();
	currentScene = memory::make_shared<Scene>(path);
}

std::shared_ptr<hexen::engine::core::Scene> hexen::engine::core::SceneManager::getCurrentScene()
{
	HEXEN_ADD_TO_PROFILE();
	return currentScene;
}

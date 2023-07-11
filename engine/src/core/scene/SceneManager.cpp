//
// Created by cx9ps3 on 11.07.2023.
//

#include "SceneManager.h"

std::shared_ptr<core::Scene> core::SceneManager::currentScene;

void core::SceneManager::loadScene(const std::string &path)
{
    currentScene = mem::make_shared<Scene>(path);
}

std::shared_ptr<core::Scene> core::SceneManager::getCurrentScene()
{
    return currentScene;
}



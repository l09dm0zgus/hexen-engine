//
// Created by cx9ps3 on 11.07.2023.
//
#pragma once

#include "Scene.h"


namespace core
{
    class SceneManager
    {
    private:
        static std::shared_ptr<Scene> currentScene;
    public:
        static void loadScene(const std::string &path);
        static std::shared_ptr<Scene> getCurrentScene();
    };
}

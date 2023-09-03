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

        /**
        * @brief Loads a scene from the specified file path.
        *
        * This function loads a scene from a file specified by the given file path.
        *
        * @param path The path of the scene file to load.
        */

        static void loadScene(const std::string &path);

        /**
        * @brief Retrieve the current scene from the SceneManager.
        *
        * This method returns a pointer to the current scene that is being managed by the SceneManager.
        * If no scene is currently set, nullptr is returned.
        *
        * @return A pointer to the current scene, or nullptr if no scene is set.
        */

        static std::shared_ptr<Scene> getCurrentScene();
    };
}

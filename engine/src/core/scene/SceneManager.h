//
// Created by cx9ps3 on 11.07.2023.
//

#ifndef HEXENEDITOR_SCENEMANAGER_H
#define HEXENEDITOR_SCENEMANAGER_H
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



#endif //HEXENEDITOR_SCENEMANAGER_H

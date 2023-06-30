//
// Created by cx9ps3 on 28.06.2023.
//

#ifndef HEXENEDITOR_SCENEHIERARCHYWINDOW_H
#define HEXENEDITOR_SCENEHIERARCHYWINDOW_H
#include <entity/scene/SceneEntity.h>
#include "GUIWindow.h"

namespace edit::gui
{
    class SceneHierarchyWindow : public GUIWindow
    {
    private:
        bool isOpen{true};
        void drawEntityChilds(const core::HashTable<std::string,std::shared_ptr<ent::SceneEntity>> &childs);
        std::shared_ptr<ent::SceneEntity> scene;
    public:
        explicit SceneHierarchyWindow(std::string name);
        void begin() override;
        void draw() override;
        void end() override;
    };
}

#endif //HEXENEDITOR_SCENEHIERARCHYWINDOW_H

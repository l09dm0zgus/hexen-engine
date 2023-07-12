//
// Created by cx9ps3 on 28.06.2023.
//

#ifndef HEXENEDITOR_SCENEHIERARCHYWINDOW_H
#define HEXENEDITOR_SCENEHIERARCHYWINDOW_H
#include <core/scene/SceneManager.h>
#include "GUIWindow.h"

namespace edit::gui
{
    class SceneHierarchyWindow : public GUIWindow
    {
    private:
        bool isOpen{true};
        void drawEntityChilds(core::HashTable<std::string,std::shared_ptr<ent::SceneEntity>> &&childs);
        void drawEntity(const std::shared_ptr<ent::SceneEntity> &entity);
        void startDragAndDropSource(const std::shared_ptr<ent::SceneEntity>& sceneEntity);
        void startDragAndDropTarget(std::shared_ptr<ent::SceneEntity>&& sceneEntity);
        void drawSearchBar();
        std::shared_ptr<core::Scene> scene;
        std::string searchQuery;
        core::HashTable<std::string,std::shared_ptr<ent::SceneEntity>> findedChilds;
        const std::string PAYLOAD_NAME{"SCENE_HIERARCHY_PAYLOAD"};
    public:
        explicit SceneHierarchyWindow(std::string name);
        void begin() override;
        void draw() override;
        void end() override;
    };
}

#endif //HEXENEDITOR_SCENEHIERARCHYWINDOW_H

//
// Created by cx9ps3 on 28.06.2023.
//

#pragma once

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
        void drawContextMenu();
        void drawAddSceneEntity();
        void drawAddChild();
        void drawDelete();
        void checkHoveredItem();

        std::shared_ptr<core::Scene> scene;
        std::shared_ptr<ent::SceneEntity>  hoveredNode;
        std::string searchQuery;
        core::HashTable<std::string,std::shared_ptr<ent::SceneEntity>> findedChilds;
        core::HashTable<std::string,bool> isNodeNameEditing;
        const std::string PAYLOAD_NAME{"SCENE_HIERARCHY_PAYLOAD"};
        bool isItemHovered{false};
    public:
        explicit SceneHierarchyWindow(std::string name);
        void begin() override;
        void draw() override;
        void end() override;
    };
}

//
// Created by cx9ps3 on 28.06.2023.
//

#pragma once

#include <core/scene/SceneManager.hpp>
#include "GUIWindow.hpp"

namespace hexen::editor::gui
{
    class SceneHierarchyWindow : public GUIWindow
    {
    private:
        bool isOpen{true};
        void drawEntityChilds(hexen::engine::core::HashTable<std::string,std::shared_ptr<hexen::engine::entity::SceneEntity>> &&childs);
        void drawEntity(const std::shared_ptr<hexen::engine::entity::SceneEntity> &entity);
        void startDragAndDropSource(const std::shared_ptr<hexen::engine::entity::SceneEntity>& sceneEntity);
        void startDragAndDropTarget(std::shared_ptr<hexen::engine::entity::SceneEntity>&& sceneEntity);
        void drawSearchBar();
        void drawContextMenu();
        void drawAddSceneEntity();
        void drawAddChild();
        void drawDelete();
        void checkHoveredItem();

        std::shared_ptr<hexen::engine::core::Scene> scene;
        std::shared_ptr<hexen::engine::entity::SceneEntity>  hoveredNode;
        std::string searchQuery;
        hexen::engine::core::HashTable<std::string,std::shared_ptr<hexen::engine::entity::SceneEntity>> findedChilds;
        hexen::engine::core::HashTable<std::string,bool> isNodeNameEditing;
        const std::string PAYLOAD_NAME{"SCENE_HIERARCHY_PAYLOAD"};
        bool isItemHovered{false};
    public:
        explicit SceneHierarchyWindow(std::string name);
        void begin() override;
        void draw() override;
        void end() override;
    };
}

//
// Created by cx9ps3 on 28.06.2023.
//

#include "SceneHierarchyWindow.h"
#include "../IconsFontAwesome5.h"
#include <misc/cpp/imgui_stdlib.h>

edit::gui::SceneHierarchyWindow::SceneHierarchyWindow(std::string name) : GUIWindow(std::move(name))
{
    setSize(glm::vec2(400,300));
    //temporary, in future scene loading will be called in SceneFileWindow/menu bar , etc
    core::SceneManager::loadScene("Main.hxscene");

    scene = core::SceneManager::getCurrentScene();
}

void edit::gui::SceneHierarchyWindow::begin()
{

}

void edit::gui::SceneHierarchyWindow::draw()
{
    ImGui::Begin(getName().c_str(),&isOpen,ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_HorizontalScrollbar);
    drawSearchBar();
    if(searchQuery.empty())
    {
        drawEntity(scene->getRootNode());
    }
    else
    {
        findedChilds.clear();
        auto result = ent::SceneEntity::searchNode(scene->getRootNode(),searchQuery,findedChilds);
        if(result)
        {
            drawEntityChilds(std::move(findedChilds));

        }
    }


    drawContextMenu();

    ImGui::End();
}

void edit::gui::SceneHierarchyWindow::end()
{

}

void edit::gui::SceneHierarchyWindow::drawEntityChilds(core::HashTable<std::string,std::shared_ptr<ent::SceneEntity>> &&childs)
{

    for(auto& child : childs)
    {
        core::i32 flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;


        if (!child.value->hasChildrens())
        {
            flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        }

        if(child.value != nullptr)
        {
            ImGui::PushID(child.key.c_str());
            bool open = ImGui::TreeNodeEx(child.value->getName().data(), flags);

            if( ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                isNodeNameEditing[child.key] = true;
            }

            if(isNodeNameEditing[child.key])
            {
                auto nodeName = child.value->getName();
                if(ImGui::InputText("##",&nodeName,ImGuiInputTextFlags_EnterReturnsTrue))
                {
                    child.value->rename(nodeName);
                    isNodeNameEditing[child.key] = false;
                }
            }

            checkHoveredItem();

            ImGui::PopID();

            bool hasChilds = child.value->hasChildrens();

            if(isItemHovered)
            {
                hoveredNode = child.value;
            }

            if(open)
            {
                startDragAndDropSource(child.value);
                startDragAndDropTarget(std::move(child.value));
            }
            if (hasChilds && open)
            {
                drawEntityChilds(std::move(child.value->getChildrens()));
                ImGui::TreePop();
            }
        }

    }

}

void edit::gui::SceneHierarchyWindow::startDragAndDropSource( const std::shared_ptr<ent::SceneEntity>& sceneEntity)
{
    if(ImGui::BeginDragDropSource())
    {
        ImGui::SetDragDropPayload(PAYLOAD_NAME.c_str(),sceneEntity.get(),sizeof(*sceneEntity));
        ImGui::EndDragDropSource();
    }
}

void edit::gui::SceneHierarchyWindow::startDragAndDropTarget(std::shared_ptr<ent::SceneEntity>&& sceneEntity)
{
    if(ImGui::BeginDragDropTarget())
    {
        if(auto payload = ImGui::AcceptDragDropPayload(PAYLOAD_NAME.c_str()))
        {
            auto draggedEntity = (ent::SceneEntity*)(payload->Data);
            if(draggedEntity != nullptr)
            {
                if(!draggedEntity->isDescendantExist(sceneEntity->getUUID()))
                {
                    draggedEntity->changeParent(sceneEntity);
                }
            }
        }
        ImGui::EndDragDropTarget();
    }
}

void edit::gui::SceneHierarchyWindow::drawSearchBar()
{
    ImGui::InputText(ICON_FA_SEARCH "" ,&searchQuery,ImGuiInputTextFlags_EnterReturnsTrue);
}

void edit::gui::SceneHierarchyWindow::drawEntity(const std::shared_ptr<ent::SceneEntity> &entity)
{
    core::i32 flags = ImGuiTreeNodeFlags_OpenOnArrow;

    ImGui::PushID(entity->getUUID().c_str());
    bool open = ImGui::TreeNodeEx(entity->getName().data(), flags);

    ImGui::PopID();
    checkHoveredItem();

    auto hasChilds = entity->hasChildrens();

    if (hasChilds && open)
    {
        drawEntityChilds(std::move(entity->getChildrens()));

        checkHoveredItem();

        ImGui::TreePop();
    }
}

void edit::gui::SceneHierarchyWindow::drawContextMenu()
{
    if(ImGui::BeginPopupContextWindow())
    {
        if(isItemHovered)
        {
            drawAddChild();
            drawDelete();
        }
        else
        {
            drawAddSceneEntity();
        }
        ImGui::EndPopup();
    }
    if(ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        isItemHovered = false;
    }
}

void edit::gui::SceneHierarchyWindow::drawAddSceneEntity()
{
    if(ImGui::MenuItem( ICON_FA_FILE  " Add Scene Entity..."))
    {
        scene->spawnEntity<ent::SceneEntity>("Scene Entity");

    }

}

void edit::gui::SceneHierarchyWindow::drawAddChild()
{
    if(ImGui::MenuItem( ICON_FA_FILE  " Add Child..."))
    {
        if(hoveredNode != nullptr)
        {
            hoveredNode->addChild<ent::SceneEntity>("Child");
        }
    }
}

void edit::gui::SceneHierarchyWindow::drawDelete()
{
    if(ImGui::MenuItem( ICON_FA_TRASH  " Delete"))
    {
        if(hoveredNode != nullptr)
        {
            auto parent = hoveredNode->getParent();

            if(parent != nullptr)
            {
                parent->removeChildByUUID(hoveredNode->getUUID());
            }
        }
    }
}

void edit::gui::SceneHierarchyWindow::checkHoveredItem()
{
    if(ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup))
    {
        isItemHovered = true;
    }
}

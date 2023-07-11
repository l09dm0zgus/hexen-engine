//
// Created by cx9ps3 on 28.06.2023.
//

#include "SceneHierarchyWindow.h"

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

    scene->forEach([this](std::shared_ptr<ent::SceneEntity>& entity){
        drawEntityChilds(std::move(entity->getChildrens()));
    });

    ImGui::End();
}

void edit::gui::SceneHierarchyWindow::end()
{

}

void edit::gui::SceneHierarchyWindow::drawEntityChilds(core::HashTable<std::string,std::shared_ptr<ent::SceneEntity>> &&childs)
{

    for(auto& child : childs)
    {
        core::i32 flags = ImGuiTreeNodeFlags_OpenOnArrow;


        if (!child.value->hasChildrens())
        {
            flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        }

        if(child.value != nullptr)
        {
            ImGui::PushID(child.key.c_str());
            bool open = ImGui::TreeNodeEx(child.value->getName().data(), flags);



            ImGui::PopID();
            bool hasChilds = child.value->hasChildrens();

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
                auto draggedEntitySharedPtr = std::shared_ptr<ent::SceneEntity>(draggedEntity);
                if(ent::SceneEntity::isNodeExist(draggedEntitySharedPtr,sceneEntity->getUUID()))
                {
                    draggedEntitySharedPtr->changeParent(sceneEntity);
                }
            }
        }
        ImGui::EndDragDropTarget();
    }
}

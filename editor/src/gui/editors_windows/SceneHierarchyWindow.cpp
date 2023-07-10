//
// Created by cx9ps3 on 28.06.2023.
//

#include "SceneHierarchyWindow.h"

edit::gui::SceneHierarchyWindow::SceneHierarchyWindow(std::string name) : GUIWindow(std::move(name))
{
    setSize(glm::vec2(400,300));
    scene = core::mem::make_shared<ent::SceneEntity>("Scene");
    scene->addChild("Scene_Entity_0");
    scene->addChild("Scene_Entity_1");
    scene->addChild("Scene_Entity_2");
    scene->getChild("Scene_Entity_2")->addChild("Scene_Entity_3");
    scene->getChild("Scene_Entity_2")->getChild("Scene_Entity_3")->addChild("Scene_Entity_4");
    scene->getChild("Scene_Entity_2")->getChild("Scene_Entity_3")->addChild("Scene_Entity_5");
}

void edit::gui::SceneHierarchyWindow::begin()
{

}

void edit::gui::SceneHierarchyWindow::draw()
{
    ImGui::Begin(getName().c_str(),&isOpen,ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_HorizontalScrollbar);

    drawEntityChilds(std::move(scene->getChildrens()));

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
                startDragAndDropTarget(std::move(child.value));
                startDragAndDropSource(child.value);
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
                std::cout << "Size: " << sizeof(*draggedEntity) << "\n";
                draggedEntity->changeParent(sceneEntity);
            }
        }
        ImGui::EndDragDropTarget();
    }
}

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

    drawEntityChilds(scene->getChildrens());

    ImGui::End();
}

void edit::gui::SceneHierarchyWindow::end()
{

}

void edit::gui::SceneHierarchyWindow::drawEntityChilds(const core::HashTable<std::string,std::shared_ptr<ent::SceneEntity>> &childs)
{
    for(const auto& child : childs)
    {
        core::i32 flags = ImGuiTreeNodeFlags_OpenOnArrow;

        //if (isObjectSelected)
        //{
        //  flags |= ImGuiTreeNodeFlags_Selected;
        //}


        if (!child.value->hasChildrens())
        {
            flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        }

        //if (isEntityEnabled)
        //{
            //ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5, 0.5, 0.5, 0.4));
        //}

        ImGui::PushID(child.value->getUUID().c_str());

        bool open = ImGui::TreeNodeEx(child.value->getName().data(), flags);
        bool hasChilds = child.value->hasChildrens();

        ImGui::PopID();

        if (hasChilds && open)
        {
            drawEntityChilds(child.value->getChildrens());
            ImGui::TreePop();
        }
    }
}

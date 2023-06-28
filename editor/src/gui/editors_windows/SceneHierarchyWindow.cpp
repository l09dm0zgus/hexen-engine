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
//    scene->getChild("Scene_Entity_2")->addChild("Scene_Entity_3");
  //  scene->getChild("Scene_Entity_2")->getChild("Scene_Entity_3")->addChild("Scene_Entity_4");
   // scene->getChild("Scene_Entity_2")->getChild("Scene_Entity_3")->addChild("Scene_Entity_5");
}

void edit::gui::SceneHierarchyWindow::begin()
{

}

void edit::gui::SceneHierarchyWindow::draw()
{
    ImGui::Begin(getName().c_str(),&isOpen,ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_HorizontalScrollbar);

    drawNode(scene);

    ImGui::End();
}

void edit::gui::SceneHierarchyWindow::end()
{

}

void edit::gui::SceneHierarchyWindow::drawNode(const std::shared_ptr<ent::SceneEntity> &sceneEntity)
{
    if(ImGui::TreeNodeEx(reinterpret_cast<core::vptr>(sceneEntity.get()),ImGuiTreeNodeFlags_OpenOnArrow,sceneEntity->getName().c_str()))
    {
        ImGui::TreePop();
        for(const auto& child : sceneEntity->getChildrens())
        {
            ImGui::Indent();
            drawNode(child.value);
        }
    }

}

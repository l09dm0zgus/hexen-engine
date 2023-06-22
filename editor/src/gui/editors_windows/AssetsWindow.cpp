//
// Created by cx9ps3 on 19.06.2023.
//
#include <core/graphics/texture/Texture.h>
#include "AssetsWindow.h"
#include <algorithm>
#include <iostream>
#include "../IconsFontAwesome5.h"
#include "../../project/Project.h"

edit::gui::AssetsWindow::AssetsWindow(std::string name) : GUIWindow(std::move(name))
{
    setSize(glm::vec2(1280,400));


    currenPath.emplace_back("Folder1");
    currenPath.emplace_back("Folder2");
    currenPath.emplace_back("Folder3");
    currenPath.emplace_back("Folder4");
    currenPath.emplace_back("Folder5");

    folderImage = core::mem::make_unique<core::rend::Texture>(pathToFolderIcon);
    soundImage = core::mem::make_unique<core::rend::Texture>(pathToSoundFileIcon);

    addImage("icons/1.png");
    addImage("icons/2.png");
    addImage("icons/3.png");

}

void edit::gui::AssetsWindow::begin()
{


}

void edit::gui::AssetsWindow::draw()
{
    static bool isOpen = true;
    ImGui::Begin(getName().c_str(),&isOpen,ImGuiWindowFlags_MenuBar);
    if(ImGui::BeginMenuBar())
    {
        for(core::i32 i = 0;i < currenPath.size(); i++)
        {
            drawNode(i);
        }
        ImGui::EndMenuBar();
    }
    pushButtonStyle();
    drawFolderButton("Test");
    drawSoundButton("music.mp3");
    drawImageButtons();
    popButtonStyle();
    if(ImGui::BeginPopupContextWindow())
    {
        if(ImGui::MenuItem("Lol"))
        {

        }
        ImGui::EndPopup();
    }
    ImGui::End();


}

void edit::gui::AssetsWindow::end()
{

}

void edit::gui::AssetsWindow::drawNode(core::i32 i)
{
    auto nodeName = currenPath[i] + " " + ICON_FA_FOLDER;

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding,50.0f);
    ImGui::PushStyleColor(ImGuiCol_Button,ImVec4(1.0f,1.0f,1.0f,0.1f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive,ImVec4(1.0f,1.0f,1.0f,0.3f));
    ImGui::ArrowButton("arrow",ImGuiDir_Right);
    ImGui::SameLine(0,0.0);
    if(ImGui::Button(nodeName.c_str()))
    {
        auto it = std::find(currenPath.begin(),currenPath.end(),currenPath[i] );
        if(it != currenPath.end())
        {
            currenPath.erase(it + 1, currenPath.end());
        }
    }

    ImGui::PopStyleVar();
    ImGui::PopStyleColor(2);
    ImGui::SameLine(0,0.0);
}

void edit::gui::AssetsWindow::addToPath(const std::string &folder)
{
    currenPath.push_back(folder);
}

void edit::gui::AssetsWindow::drawFolderButton(const std::string &folderName)
{
   auto callback = [](auto &fullPathToCallback)
   {

   };
   drawImageButton(folderName,"",folderImage->getId(),callback);
}

void edit::gui::AssetsWindow::pushButtonStyle()
{
    ImGui::PushStyleColor(ImGuiCol_Button,ImVec4(0.0f,0.0f,0.0f,0.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,ImVec4(1.0f,1.0f,1.0f,0.1f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive,ImVec4(1.0f,1.0f,1.0f,0.1f));

}

void edit::gui::AssetsWindow::popButtonStyle()
{
    ImGui::PopStyleColor(3);
}

void edit::gui::AssetsWindow::drawSoundButton(const std::string &fileName)
{
    auto callback = [](auto &fullPathToCallback)
    {

    };
    drawImageButton(fileName,"",soundImage->getId(),callback);
}

void edit::gui::AssetsWindow::addImage(const std::string &pathToImage)
{
    images.set(pathToImage,std::make_shared<core::rend::Texture>(pathToImage));
}

void edit::gui::AssetsWindow::drawImageButtons()
{
    for(auto& image : images)
    {
        auto fileName = std::filesystem::path(image.key).filename().string();

        auto callback = [](auto &fullPathToCallback)
        {

        };
        drawImageButton(fileName,"",image.value->getId(),callback);
    }
}

void edit::gui::AssetsWindow::drawImageButton(const std::string &fileName,const std::string &fullPathToFile,core::u32 textureId,const std::function<void(const std::string& )>& callback)
{
    ImGui::BeginGroup();
    if(ImGui::ImageButton((ImTextureID)textureId, ImVec2(iconsSize.x,iconsSize.y)))
    {
        callback(fullPathToFile);
    }
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (iconsSize.x / 2) * 0.5f);
    ImGui::Text(fileName.c_str());
    ImGui::EndGroup();
    ImGui::SameLine();
}


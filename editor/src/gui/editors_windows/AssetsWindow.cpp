//
// Created by cx9ps3 on 19.06.2023.
//

#include "AssetsWindow.h"
#include <algorithm>
#include <iostream>
#include "../IconsFontAwesome5.h"


edit::gui::AssetsWindow::AssetsWindow(std::string name) : GUIWindow(std::move(name))
{
    setSize(glm::vec2(1280,400));

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefault();
    float baseFontSize = 16.0f; // 13.0f is the size of the default font. Change to the font size you use.
    float iconFontSize = baseFontSize * 2.0f / 3.0f; // FontAwesome fonts need to have their sizes reduced by 2.0f/3.0f in order to align correctly


    static const ImWchar iconsRanges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0};

    ImFontConfig iconsConfig;
    iconsConfig.MergeMode = true;
    iconsConfig.GlyphMinAdvanceX = iconFontSize;
    iconsConfig.PixelSnapH = true;

    io.Fonts->AddFontFromFileTTF( "fonts/fa-solid-900.ttf", iconFontSize,&iconsConfig,iconsRanges);

    currenPath.emplace_back("Folder1");
    currenPath.emplace_back("Folder2");
    currenPath.emplace_back("Folder3");
    currenPath.emplace_back("Folder4");
    currenPath.emplace_back("Folder5");



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


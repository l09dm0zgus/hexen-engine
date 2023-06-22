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

    folderImage = core::mem::make_unique<core::rend::Texture>(pathToFolderIcon);
    soundImage = core::mem::make_unique<core::rend::Texture>(pathToSoundFileIcon);
    rows = static_cast<core::i32>(getSize().x / iconsSize.x);
}

void edit::gui::AssetsWindow::begin()
{


}

void edit::gui::AssetsWindow::draw()
{
    ImGui::Begin(getName().c_str(),&isOpen,ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_HorizontalScrollbar);

    if(Project::getCurrentProject() != nullptr)
    {
        if(!isRootDirectoryLoaded)
        {
            currentPath = Project::getCurrentProject()->getPath();
            isRootDirectoryLoaded = true;
            directoryList.emplace_back("/");
            indexFilesInDirectory();
        }

        if(ImGui::BeginMenuBar())
        {
            for(core::i32 i = 0; i < directoryList.size(); i++)
            {
                drawNode(i);
            }
            ImGui::EndMenuBar();
        }

        auto panelWitdh = ImGui::GetContentRegionAvail().x;
        auto cellSize = iconsSize.x + padding;
        auto columnNumber = static_cast<core::i32>(panelWitdh / cellSize);

        ImGui::Columns(columnNumber, nullptr, false);
        showFilesInDirectory();
        ImGui::Columns(1);

        ImGui::SliderFloat("Icon Size" , &iconsSize.x,16,256);
        iconsSize.y = iconsSize.x;

        ImGui::SliderFloat("Padding" , &padding,0,32);

        if(ImGui::BeginPopupContextWindow())
        {
            if(ImGui::MenuItem("Lol"))
            {

            }
            ImGui::EndPopup();
        }
    }
    ImGui::End();
}

void edit::gui::AssetsWindow::end()
{

}

void edit::gui::AssetsWindow::drawNode(core::i32 i)
{
    auto nodeName = directoryList[i] + " " + ICON_FA_FOLDER;

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding,50.0f);
    ImGui::PushStyleColor(ImGuiCol_Button,ImVec4(1.0f,1.0f,1.0f,0.1f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive,ImVec4(1.0f,1.0f,1.0f,0.3f));
    ImGui::ArrowButton("arrow",ImGuiDir_Right);
    ImGui::SameLine(0,0.0);
    if(ImGui::Button(nodeName.c_str()))
    {
        auto it = std::find(directoryList.begin(), directoryList.end(), directoryList[i] );
        if(it != directoryList.end())
        {
            directoryList.erase(it + 1, directoryList.end());
        }
    }

    ImGui::PopStyleVar();
    ImGui::PopStyleColor(2);
}

void edit::gui::AssetsWindow::addToPath(const std::string &folder)
{
    directoryList.push_back(folder);
}

void edit::gui::AssetsWindow::drawFolderButton(const std::string &folderName)
{
   auto callback = [](auto &fullPathToCallback)
   {

   };
    drawButton(folderName, "", folderImage->getId(), callback);
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
    drawButton(fileName, "", soundImage->getId(), callback);
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
        drawButton(fileName, "", image.value->getId(), callback);
    }
}

void edit::gui::AssetsWindow::drawButton(const std::string &fileName, const std::string &fullPathToFile, core::u32 textureId, const std::function<void(const std::string& )>& callback)
{
    if(ImGui::ImageButton((ImTextureID)textureId, ImVec2(iconsSize.x,iconsSize.y)))
    {
        callback(fullPathToFile);
    }
    ImGui::Text(fileName.c_str());
    ImGui::NextColumn();

}

void edit::gui::AssetsWindow::showFilesInDirectory()
{
    pushButtonStyle();

    drawFolderButtons();
    drawSoundButtons();
    drawImageButtons();

    popButtonStyle();
}

void edit::gui::AssetsWindow::drawOnSameLine()
{
    //ImGui::SameLine();
}

void edit::gui::AssetsWindow::indexFilesInDirectory()
{
    folderNames.clear();
    soundFilesNames.clear();
    images.clear();

    for(const auto& path : std::filesystem::directory_iterator(currentPath))
    {
        auto name = path.path().filename().string();
        auto extension = path.path().extension().string();
        if(path.is_directory())
        {
            folderNames.push_back(name);
        }
        else
        {
            auto isImage = std::find(imageFileExtensions.cbegin(),imageFileExtensions.cend(),extension);
            auto isAudio = std::find(soundFileExtensions.cbegin(),soundFileExtensions.cend(),extension);
            if(isImage != imageFileExtensions.cend())
            {
                addImage(path.path().string());
            }
            else if(isAudio != soundFileExtensions.cend())
            {
                soundFilesNames.push_back(name);
            }
        }
    }
}

void edit::gui::AssetsWindow::drawSoundButtons()
{
    for(const auto& name : soundFilesNames)
    {
        drawSoundButton(name);
    }
}

void edit::gui::AssetsWindow::drawFolderButtons()
{
    for(const auto& name : folderNames)
    {
        drawFolderButton(name);
    }
}


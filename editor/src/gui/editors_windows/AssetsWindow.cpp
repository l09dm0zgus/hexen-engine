//
// Created by cx9ps3 on 19.06.2023.
//
#include <core/graphics/texture/Texture.h>
#include "AssetsWindow.h"
#include <algorithm>
#include <iostream>
#include "../IconsFontAwesome5.h"
#include "../../project/Project.h"

std::unique_ptr<core::rend::Texture> edit::gui::AssetIcon::fileIcon;
std::unique_ptr<core::rend::Texture> edit::gui::AssetIcon::animationFileIcon;
std::unique_ptr<core::rend::Texture> edit::gui::AssetIcon::entityFileIcon;
std::unique_ptr<core::rend::Texture> edit::gui::AssetIcon::folderIcon;
std::unique_ptr<core::rend::Texture> edit::gui::AssetIcon::sceneFileIcon;
std::unique_ptr<core::rend::Texture> edit::gui::AssetIcon::soundFileIcon;
std::unique_ptr<core::rend::Texture> edit::gui::AssetIcon::tilesetFileIcon;
edit::gui::AssetsWindow* edit::gui::AssetIcon::assetsWindow{nullptr};

edit::gui::AssetsWindow::AssetsWindow(std::string name) : GUIWindow(std::move(name))
{
    setSize(glm::vec2(1280,400));
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

        if(ImGui::SliderFloat("Icon Size" , &iconsSize.x,16,256))
        {
            iconsSize.y = iconsSize.x;
            resizeIcons();
        };

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

        currentPath = Project::getCurrentProject()->getPath();
        for(const auto& directory : directoryList)
        {
            if(directory != "/")
            {
                currentPath = currentPath / directory;
            }
        }
        indexFilesInDirectory();
    }
    ImGui::SameLine(0,0.0);
    ImGui::PopStyleVar();
    ImGui::PopStyleColor(2);
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

void edit::gui::AssetsWindow::showFilesInDirectory()
{
    pushButtonStyle();
    for(auto& icon : icons)
    {
        icon.draw();
    }
    popButtonStyle();
}


void edit::gui::AssetsWindow::indexFilesInDirectory()
{
    icons.clear();
    for(const auto& path : std::filesystem::directory_iterator(currentPath))
    {
        icons.emplace_back(path, this);
    }
}

void edit::gui::AssetsWindow::resizeIcons()
{
    for(auto& icon : icons)
    {
        icon.setSize(iconsSize);
    }
}

edit::gui::AssetIcon::AssetIcon(const std::filesystem::directory_entry &path, AssetsWindow *newAssetsWindow)
{

    name = path.path().filename();
    pathToFile = path.path().string();
    assetsWindow = newAssetsWindow;

    if(fileIcon == nullptr)
    {
        //use static class members for memory optimization

        folderIcon = core::mem::make_unique<core::rend::Texture>(pathToFolderIcon);
        soundFileIcon = core::mem::make_unique<core::rend::Texture>(pathToSoundFileIcon);
        fileIcon = core::mem::make_unique<core::rend::Texture>(pathToFileIcon);
        sceneFileIcon = core::mem::make_unique<core::rend::Texture>(pathToSceneFileIcon);
        animationFileIcon = core::mem::make_unique<core::rend::Texture>(pathToAnimationFileIcon);
        tilesetFileIcon = core::mem::make_unique<core::rend::Texture>(pathToTilesetFileIcon);
        entityFileIcon = core::mem::make_unique<core::rend::Texture>(pathToEntityFileIcon);
    }

    engineFileExtensions.set(sceneFileIcon->getId(),".hxscene");
    engineFileExtensions.set(animationFileIcon->getId(),".hxanim");
    engineFileExtensions.set(tilesetFileIcon->getId(),".hxtile");
    engineFileExtensions.set(entityFileIcon->getId(),".hxentity");

    if (path.is_directory())
    {
        textureId = folderIcon->getId();
        callback = [this](const std::string &path){
            auto fileName = std::filesystem::path(path).filename().string();
            assetsWindow->directoryList.push_back(fileName);
            assetsWindow->currentPath = assetsWindow->currentPath / fileName;
            assetsWindow->indexFilesInDirectory();
        };
    }
    else
    {
        auto extension = name.extension().string();
        auto isImage = std::find(imageFileExtensions.cbegin(),imageFileExtensions.cend(),extension);
        auto isAudio = std::find(soundFileExtensions.cbegin(),soundFileExtensions.cend(),extension);
        auto isEngineFile = std::find_if(engineFileExtensions.begin(),engineFileExtensions.end(),[&extension](const auto &keyValue){
            return keyValue.value == extension;
        });

        if(isImage != imageFileExtensions.cend())
        {
            this->callback = [this](auto &fullPathToFile){

            };

            imageFileIcon = core::mem::make_unique<core::rend::Texture>(path.path().string());
            textureId = imageFileIcon->getId();
        }
        else if(isAudio != soundFileExtensions.cend())
        {
            this->callback = [this](auto &fullPathToFile){

            };

            textureId = soundFileIcon->getId();
        }
        else if(isEngineFile != engineFileExtensions.cend())
        {
            this->callback = [this](auto &fullPathToFile){

            };

            textureId = isEngineFile->key;
        }
        else
        {
            this->callback = [this](auto &fullPathToFile){

            };

            textureId = fileIcon->getId();
        }
    }

}

void edit::gui::AssetIcon::setSize(const glm::vec2 &newSize)
{
    size = newSize;
}

void edit::gui::AssetIcon::draw()
{
    if(ImGui::ImageButton(name.string().c_str(),(ImTextureID)textureId, ImVec2(size.x,size.y)))
    {
        callback(pathToFile);
    }
    ImGui::Text(name.string().c_str());
    ImGui::NextColumn();
}


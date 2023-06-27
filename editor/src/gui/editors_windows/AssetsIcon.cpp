//
// Created by cx9ps3 on 27.06.2023.
//

#include "AssetsIcon.h"
#include "AssetsWindow.h"
#include <misc/cpp/imgui_stdlib.h>

std::unique_ptr<core::rend::Texture> edit::gui::AssetIcon::fileIcon;
std::unique_ptr<core::rend::Texture> edit::gui::AssetIcon::animationFileIcon;
std::unique_ptr<core::rend::Texture> edit::gui::AssetIcon::entityFileIcon;
std::unique_ptr<core::rend::Texture> edit::gui::AssetIcon::folderIcon;
std::unique_ptr<core::rend::Texture> edit::gui::AssetIcon::sceneFileIcon;
std::unique_ptr<core::rend::Texture> edit::gui::AssetIcon::soundFileIcon;
std::unique_ptr<core::rend::Texture> edit::gui::AssetIcon::tilesetFileIcon;
edit::gui::AssetsWindow* edit::gui::AssetIcon::assetsWindow{nullptr};
core::HashTable<core::u32,std::string> edit::gui::AssetIcon::engineFileExtensions;

edit::gui::AssetIcon::AssetIcon(const std::filesystem::directory_entry &path, AssetsWindow *newAssetsWindow)
{

    name = path.path().filename();
    pathToFile = path.path().string();
    fileName = name.string();

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

        engineFileExtensions.set(sceneFileIcon->getId(),".hxscene");
        engineFileExtensions.set(animationFileIcon->getId(),".hxanim");
        engineFileExtensions.set(tilesetFileIcon->getId(),".hxtile");
        engineFileExtensions.set(entityFileIcon->getId(),".hxentity");
    }

    if (path.is_directory())
    {
        textureId = folderIcon->getId();
        callback = [this](const std::string &path){
            auto filename = std::filesystem::path(path).filename().string();
            assetsWindow->directoryList.push_back(filename);
            assetsWindow->currentPath = assetsWindow->currentPath / filename;
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
    isCtrlPressed = ImGui::IsKeyDown(ImGuiKey_LeftCtrl);
    ImGui::PushStyleColor(ImGuiCol_Button,color);
    isClicked = ImGui::ImageButton(name.string().c_str(),(ImTextureID)textureId, ImVec2(size.x,size.y));
    setAssetWindowHoveredIcon();

    createDragAndDropSource();

    selectingFiles();

    createDragAndDropTarget();

    ImGui::PopStyleColor();

    showFilename();
    setAssetWindowHoveredIcon();

    ImGui::NextColumn();
}

void edit::gui::AssetIcon::createDragAndDropSource()
{
    if(ImGui::BeginDragDropSource())
    {
        ImGui::SetDragDropPayload(PAYLOAD_NAME.c_str(),pathToFile.c_str(),(pathToFile.size() + 1) * sizeof(char));
        ImGui::EndDragDropSource();
    }
}

void edit::gui::AssetIcon::createDragAndDropTarget()
{
    if(ImGui::BeginDragDropTarget())
    {
        if(auto payload = ImGui::AcceptDragDropPayload(PAYLOAD_NAME.c_str()))
        {
            auto draggedFilePath = (char *)payload->Data;
            std::filesystem::path fileToMove(draggedFilePath);
            if(std::filesystem::is_directory(pathToFile))
            {
                std::filesystem::rename(fileToMove,pathToFile / fileToMove.filename());
                assetsWindow->indexFilesInDirectory();
            }
        }
        ImGui::EndDragDropTarget();
    }
}

void edit::gui::AssetIcon::showFilename()
{
    if(!isEditingName)
    {
        ImGui::TextWrapped(name.string().c_str());
        if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
            isEditingName = true;
        }
    }
    else
    {


        if(ImGui::InputText("##",&fileName,ImGuiInputTextFlags_EnterReturnsTrue))
        {
            auto path = std::filesystem::path(pathToFile).parent_path();
            std::filesystem::rename(pathToFile,path / fileName);
            assetsWindow->indexFilesInDirectory();
            isEditingName = false;
        }
    }
}

void edit::gui::AssetIcon::selectingFiles()
{
    if(isCtrlPressed && isClicked)
    {
        color = ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered];
        assetsWindow->selectedFiles.emplace_back(pathToFile);
    }
    else if(isClicked)
    {
        color = {0.0f,0.0f,0.0f,0.0f};
        assetsWindow->selectedFiles.clear();
        callback(pathToFile);
    }
    else if(ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
    {
        color = {0.0f,0.0f,0.0f,0.0f};
        assetsWindow->selectedFiles.clear();
    }
}


std::string edit::gui::AssetIcon::getPath() const noexcept
{
    return pathToFile;
}

void edit::gui::AssetIcon::setAssetWindowHoveredIcon()
{
    if(ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenBlockedByPopup))
    {
        assetsWindow->currentHoveredIcon = this;
    }
}

void edit::gui::AssetIcon::renameFile()
{
    isEditingName = true;
}

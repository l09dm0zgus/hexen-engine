//
// Created by cx9ps3 on 27.06.2023.
//

#ifndef HEXENEDITOR_ASSETSICON_H
#define HEXENEDITOR_ASSETSICON_H
#include <core/graphics/texture/Texture.h>
#include <filesystem>
#include <glm/glm.hpp>
#include <imgui.h>

namespace edit::gui
{
    class AssetsWindow;
    class AssetIcon
    {
    private:
        static std::unique_ptr<core::rend::Texture> folderIcon;
        static std::unique_ptr<core::rend::Texture> soundFileIcon;
        static std::unique_ptr<core::rend::Texture> fileIcon;
        static std::unique_ptr<core::rend::Texture> sceneFileIcon;
        static std::unique_ptr<core::rend::Texture> animationFileIcon;
        static std::unique_ptr<core::rend::Texture> tilesetFileIcon;
        static std::unique_ptr<core::rend::Texture> entityFileIcon;
        static AssetsWindow *assetsWindow;
        static core::HashTable<core::u32,std::string> engineFileExtensions;

        std::unique_ptr<core::rend::Texture> imageFileIcon;

        std::string pathToFolderIcon = "icons/folder.png";
        std::string pathToSoundFileIcon = "icons/music.png";
        std::string pathToFileIcon = "icons/file.png";
        std::string pathToSceneFileIcon = "icons/scene.png";
        std::string pathToAnimationFileIcon = "icons/animation.png";
        std::string pathToTilesetFileIcon = "icons/tileset.png";
        std::string pathToEntityFileIcon = "icons/entity.png";

        std::vector<std::string> imageFileExtensions{".png",".jpeg",".bmp",".tga",".jpg",".gif"};
        std::vector<std::string> soundFileExtensions{".wav", ".ogg",".mp3",".flac"};

        std::filesystem::path name;
        std::string pathToFile;

        glm::vec2 size{64.0f};
        core::u32 textureId;
        std::function<void(const std::string& )> callback;
        bool isCtrlPressed{false};
        bool isClicked{false};
        bool isEditingName{false};
        bool bIsHovered{false};
        char *fileName{};
        ImVec4 color;
        const std::string PAYLOAD_NAME = "ASSET_WINDOW_ITEM";
        void createDragAndDropSource();
        void createDragAndDropTarget();
        void showFilename();
        void selectingFiles();
    public:
        explicit AssetIcon(const std::filesystem::directory_entry &path, AssetsWindow *newAssetsWindow);
        bool isHovered() const noexcept;
        void setSize(const glm::vec2 &newSize);
        void renameFile();
        std::string getPath() const noexcept;
        void draw();
    };
}

#endif //HEXENEDITOR_ASSETSICON_H

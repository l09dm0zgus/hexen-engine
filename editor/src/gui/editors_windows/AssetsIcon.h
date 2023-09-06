//
// Created by cx9ps3 on 27.06.2023.
//

#pragma once

#include <core/graphics/texture/Texture.h>
#include <filesystem>
#include <glm/glm.hpp>
#include <imgui.h>

namespace hexen::editor::gui
{
    class AssetsWindow;
    class AssetIcon
    {
    private:
        static std::unique_ptr<hexen::engine::graphics::gl::Texture> folderIcon;
        static std::unique_ptr<hexen::engine::graphics::gl::Texture> soundFileIcon;
        static std::unique_ptr<hexen::engine::graphics::gl::Texture> fileIcon;
        static std::unique_ptr<hexen::engine::graphics::gl::Texture> sceneFileIcon;
        static std::unique_ptr<hexen::engine::graphics::gl::Texture> animationFileIcon;
        static std::unique_ptr<hexen::engine::graphics::gl::Texture> tilesetFileIcon;
        static std::unique_ptr<hexen::engine::graphics::gl::Texture> entityFileIcon;
        static AssetsWindow *assetsWindow;
        static hexen::engine::core::HashTable<hexen::engine::core::u32,std::string> engineFileExtensions;

        std::unique_ptr<hexen::engine::graphics::gl::Texture> imageFileIcon;

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
        engine::core::u32 textureId;
        std::function<void(const std::string& )> callback;
        bool isCtrlPressed{false};
        bool isClicked{false};
        bool isEditingName{false};
        bool bIsHovered{false};
        std::string fileName{};
        ImVec4 color;
        const std::string PAYLOAD_NAME = "ASSET_WINDOW_ITEM";
        void createDragAndDropSource();
        void createDragAndDropTarget();
        void showFilename();
        void selectingFiles();
        void setAssetWindowHoveredIcon();
    public:
        explicit AssetIcon(const std::filesystem::directory_entry &path, AssetsWindow *newAssetsWindow);
        void setSize(const glm::vec2 &newSize);
        void renameFile();
        [[nodiscard]] std::string getPath() const noexcept;
        void draw();
    };
}

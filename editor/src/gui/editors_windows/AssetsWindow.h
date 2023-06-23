//
// Created by cx9ps3 on 19.06.2023.
//

#ifndef HEXENEDITOR_ASSETSWINDOW_H
#define HEXENEDITOR_ASSETSWINDOW_H
#include "GUIWindow.h"
#include "../../project/Project.h"
#include <core/graphics/texture/Texture.h>

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
        core::HashTable<core::u32,std::string> engineFileExtensions;
        std::filesystem::path name;
        std::string pathToFile;

        glm::vec2 size{64.0f};
        core::u32 textureId;
        std::function<void(const std::string& )> callback;
        static  AssetsWindow *assetsWindow;
    public:
        explicit AssetIcon(const std::filesystem::directory_entry &path, AssetsWindow *newAssetsWindow);
        void setSize(const glm::vec2 &newSize);
        void draw();
    };

    class AssetsWindow : public GUIWindow
    {
    private:
        void drawNode(core::i32 i);
        void pushButtonStyle();
        void popButtonStyle();
        void showFilesInDirectory();
        void resizeIcons();
        std::vector<AssetIcon> icons;

        bool isOpen{true};
        bool isRootDirectoryLoaded{false};
        glm::vec2 iconsSize{64.0f};
        float padding{16.0f};
        std::vector<std::string> directoryList;
        std::filesystem::path currentPath;
        friend class AssetIcon;
    public:
        explicit AssetsWindow(std::string name);

        std::vector<std::string> getDirectories() const noexcept {return directoryList;}
        std::filesystem::path getCurrentPath() const noexcept{ return currentPath;}

        template<class T>
        void setDirectories(T&& directories) { directoryList = std::forward<T>(directories); }

        template<class T>
        void setCurrentPath(T&& path) { currentPath = std::forward<T>(path); }
        void indexFilesInDirectory();

        void begin() override;
        void draw() override;
        void end() override;
    };
}


#endif //HEXENEDITOR_ASSETSWINDOW_H

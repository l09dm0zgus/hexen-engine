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
    class AssetsWindow : public GUIWindow
    {
    private:
        void drawNode(core::i32 i);
        void addToPath(const std::string &folder);
        std::vector<std::string> directoryList;
        std::filesystem::path currentPath;

        void pushButtonStyle();
        void popButtonStyle();

        std::vector<std::string> folderNames;
        std::vector<std::string> soundFilesNames;

        void indexFilesInDirectory();

        void drawFolderButton(const std::string &folderName);
        void drawSoundButton(const std::string &fileName);

        void drawButton(const std::string &fileName, const std::string &fullPathToFile, core::u32 textureId, const std::function<void(const std::string& )>& callback);
        void drawImageButtons();
        void drawSoundButtons();
        void drawFolderButtons();

        void addImage(const std::string &pathToImage);

        glm::vec2 iconsSize{64.0f};
        float padding{16.0f};

        std::unique_ptr<core::rend::Texture> folderImage;
        std::unique_ptr<core::rend::Texture> soundImage;
        std::string pathToFolderIcon = "icons/folder.png";
        std::string pathToSoundFileIcon = "icons/music.png";
        core::HashTable<std::string,std::shared_ptr<core::rend::Texture>> images;

        void showFilesInDirectory();
        std::vector<std::string> imageFileExtensions{".png",".jpeg",".bmp",".tga",".jpg",".gif"};
        std::vector<std::string> soundFileExtensions{".wav", ".ogg",".mp3",".flac"};

        bool isOpen{true};
        bool isRootDirectoryLoaded{false};
    public:
        explicit AssetsWindow(std::string name);
        void begin() override;
        void draw() override;
        void end() override;
    };
}


#endif //HEXENEDITOR_ASSETSWINDOW_H

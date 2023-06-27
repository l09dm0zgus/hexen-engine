//
// Created by cx9ps3 on 19.06.2023.
//

#ifndef HEXENEDITOR_ASSETSWINDOW_H
#define HEXENEDITOR_ASSETSWINDOW_H
#include "GUIWindow.h"
#include "../../project/Project.h"
#include <core/graphics/texture/Texture.h>
#include "dialogs/DeleteSelectedFilesWindow.h"
#include "dialogs/CopyingFilesWindow.h"
#include "AssetsIcon.h"

namespace edit::gui
{
    class AssetsWindow : public GUIWindow
    {
    private:
        void drawNode(core::i32 i);
        void pushButtonStyle();
        void popButtonStyle();
        void showFilesInDirectory();
        void resizeIcons();
        void drawImportNewAssets();
        void drawDelete();
        void drawRename();
        void drawMenu();
        void refresh();
        void getActionsFromDialogs();
        std::vector<AssetIcon> icons;

        bool isOpen{true};
        bool isRootDirectoryLoaded{false};
        glm::vec2 iconsSize{64.0f};
        float padding{16.0f};
        std::vector<std::string> directoryList;
        std::filesystem::path currentPath;
        friend class AssetIcon;

        std::vector<std::filesystem::path> selectedFiles;
        std::function<void()> deleteSelectedFilesCallback;

        std::unique_ptr<DeleteFileWindow> deleteFileWindow;
        std::unique_ptr<DeleteSelectedFilesWindow> deleteSelectedFilesWindow;
        std::unique_ptr<CopyingFilesWindow> copyingFilesWindow;

        std::vector<DialogWindow::Action> dialogWindowActions;
        AssetIcon *currentHoveredIcon{nullptr};
        bool isShowedContextMenu{false};

    public:
        explicit AssetsWindow(std::string name);

        void begin() override;
        void draw() override;
        void end() override;
    };
}


#endif //HEXENEDITOR_ASSETSWINDOW_H

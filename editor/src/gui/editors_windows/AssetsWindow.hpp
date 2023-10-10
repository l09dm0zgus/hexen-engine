//
// Created by cx9ps3 on 19.06.2023.
//

#pragma once

#include "../../project/Project.hpp"
#include "AssetsIcon.hpp"
#include "GUIWindow.hpp"
#include "dialogs/CopyingFilesWindow.hpp"
#include "dialogs/DeleteSelectedFilesWindow.hpp"
#include "graphics/textures/GL/GLTexture2D.hpp"

namespace hexen::editor::gui
{
	/**
 	* @class AssetsWindow
 	* @brief A sub-class of GUIWindow for handling operations related to assets.
 	*
 	* Extends the functionality of a GUIWindow to add operations specific to asset handling.
	* This includes operations such as drawing nodes, handling menu interactions, drawing the UI, and more.
 	*/

	class AssetsWindow : public GUIWindow
	{
	private:
		/** @brief Draws a node.
		 * @param i The index of the node to draw.
		 */
		void drawNode(engine::core::i32 i);

		/** @brief Sets the style for a button when it's pressed. */
		void pushButtonStyle();

		/** @brief Reverts the style changes made by pushButtonStyle(). */
		void popButtonStyle();

		/** @brief Displays files in a directory. */
		void showFilesInDirectory();

		/** @brief Resizes the icons. */
		void resizeIcons();

		/** @brief Handles user interactions with the Import New Assets function. */
		void drawImportNewAssets();

		/** @brief Handles user interactions with the Delete function. */
		void drawDelete();

		/** @brief Handles user interactions with the Rename function. */
		void drawRename();

		/** @brief Draws the asset window menu. */
		void drawMenu();

		/** @brief Handles user interactions with the Create New Folder function. */
		void drawNewFolder();

		/** @brief Handles user interactions with the Refresh function. */
		void drawRefresh();

		/** @brief Handles user interactions with the Create Scene function. */
		void drawCreateScene();

		/** @brief Handles user interactions with the Create Tileset function. */
		void drawCreateTileset();

		/** @brief Handles user interactions with the Create Animation function. */
		void drawCreateAnimation();

		/** @brief Handles user interactions with the Create Entity function. */
		void drawCreateEntity();

		/** @brief Reloads the state of the assets window. */
		void refresh();

		/** @brief Retrieves actions from dialog windows. */
		void getActionsFromDialogs();

		/** @brief Icons for representing assets visually. */
		std::vector<AssetIcon> icons;

		/** @brief The open state of the window. */
		bool isOpen {true};

		/** @brief State if root directory is loaded. */
		bool isRootDirectoryLoaded {false};

		/** @brief Icon size in the window. */
		glm::vec2 iconsSize {64.0f};

		/** @brief Padding size. */
		float padding {16.0f};

		/** @brief List of directories present. */
		std::vector<std::string> directoryList;

		/** @brief The current path that the window is showing. */
		std::filesystem::path currentPath;
		friend class AssetIcon;

		/** @brief The currently selected files. */
		std::vector<std::filesystem::path> selectedFiles;

		/** @brief Callback function when selected files are deleted. */
		std::function<void()> deleteSelectedFilesCallback;

		/** @brief Callback function when refresh is needed. */
		std::function<void()> refreshCallback;

		/** @brief Window for deleting individual files. */
		std::unique_ptr<DeleteFileWindow> deleteFileWindow;

		/** @brief Window for deleting multiple selected files. */
		std::unique_ptr<DeleteSelectedFilesWindow> deleteSelectedFilesWindow;

		/** @brief Window for copying files. */
		std::unique_ptr<CopyingFilesWindow> copyingFilesWindow;

		/** @brief Actions from dialog windows. */
		std::vector<DialogWindow::Action> dialogWindowActions;

		/** @brief Current hovered icon for asset manipulation. */
		AssetIcon *currentHoveredIcon {nullptr};

		/** @brief The context menu visibility state. */
		bool isShowedContextMenu {false};

	public:
		/** @brief Constructor.
		 * @param name The name of the window.
		 */
		explicit AssetsWindow(std::string name);

		/** @brief Begins drawing of the window. Overrides the function in GUIWindow. */
		void begin() override;

		/** @brief Handles drawing of the window. Overrides the function in GUIWindow. */
		void draw() override;

		/** @brief Ends drawing of the window. Overrides the function in GUIWindow. */
		void end() override;
	};
}// namespace hexen::editor::gui